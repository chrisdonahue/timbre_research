#include "sample_buffer.hpp"

cdsp::sample_buffer::sample_buffer() {
	channels_num = 0;
	channel_buffer_length = 0;
	buffer_length = 0;
	buffer = nullptr;
}


cdsp::sample_buffer::sample_buffer(types::channel _channels_num, types::disc_32_u _channel_buffer_length) {
	channels_num = _channels_num;
	channel_buffer_length = _channel_buffer_length;
	buffer_length = 0;
	buffer = nullptr;
	buffer_reallocate();
}

cdsp::sample_buffer::~sample_buffer() {
	buffer_free();
}

void cdsp::sample_buffer::buffer_reallocate() {
	buffer_length = channels_num * channel_buffer_length;
	buffer = reinterpret_cast<types::sample*>(malloc(sizeof(types::sample) * buffer_length));
}

void cdsp::sample_buffer::buffer_free() {
	channels_num = 0;
	channel_buffer_length = 0;
	if (buffer != nullptr) {
		buffer_length = 0;
		free(buffer);
		buffer = nullptr;
	}
}

void cdsp::sample_buffer::resize(types::channel _channels_num, types::disc_32_u _channel_buffer_length) {
	buffer_free();
	channels_num = _channels_num;
	channel_buffer_length = _channel_buffer_length;
	if (!(channels_num & channel_buffer_length)) {
		buffer_reallocate();
	}
}

cdsp::types::disc_32_u cdsp::sample_buffer::channels_num_get() {
	return channels_num;
}

cdsp::types::disc_32_u cdsp::sample_buffer::channel_buffer_length_get() {
	return channel_buffer_length;
}

cdsp::types::disc_32_u cdsp::sample_buffer::buffer_length_get() {
	return buffer_length;
}

cdsp::types::size cdsp::sample_buffer::buffer_size_get() {
	return sizeof(types::sample) * buffer_length;
}

const cdsp::types::sample* cdsp::sample_buffer::channel_pointer_read(types::channel channel, types::disc_32_u offset) const {
	return const_cast<types::sample*>(buffer + (channel * buffer_length) + offset);
}

cdsp::types::sample* cdsp::sample_buffer::channel_pointer_write(types::channel channel, types::disc_32_u offset) {
	return buffer + (channel * buffer_length) + offset;
}

void cdsp::sample_buffer::channel_clear(types::channel channel) {
	types::sample* channel_buffer = channel_pointer_write(channel);
	types::disc_32_u samples_remaining = channel_buffer_length;
	while (samples_remaining--) {
		*(channel_buffer++) = values::sample_silence;
	}
}

void cdsp::sample_buffer::clear() {
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		channel_clear(channel);
	}
}

void cdsp::sample_buffer::channel_gain_apply(types::channel channel, types::sample gain) {
	types::sample* channel_buffer = channel_pointer_write(channel);
	types::disc_32_u samples_remaining = channel_buffer_length;
	while (samples_remaining--) {
		*(channel_buffer++) *= gain;
	}
}

void cdsp::sample_buffer::gain_apply(types::sample gain) {
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		channel_gain_apply(channel, gain);
	}
}

void cdsp::sample_buffer::channel_dc_filter(types::channel channel, types::sample r) {
	// https://ccrma.stanford.edu/~jos/filters/DC_Blocker.html
	types::sample xm1 = values::sample_silence;
	types::sample ym1 = values::sample_silence;
	types::sample x;
	types::sample y;
	types::sample* channel_buffer = channel_pointer_write(channel);
	types::disc_32_u samples_remaining = channel_buffer_length;
	while (samples_remaining--) {
		x = *(channel_buffer++);
		y = x - xm1 + r * ym1;
		xm1 = x;
		ym1 = y;
	}
}

void cdsp::sample_buffer::dc_filter() {
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		channel_dc_filter(channel);
	}
}

void cdsp::sample_buffer::channel_normalize(types::channel channel) {
	const types::sample* channel_buffer = channel_pointer_read(channel);

	// find max
	types::sample current;
	types::sample max = values::sample_infinity_n;
	types::disc_32_u samples_remaining = channel_buffer_length;
	while (samples_remaining--) {
		current = *channel_buffer++;
		if (current > max) {
			max = current;
		}
	}

	// protect against divide by zero
	if (max == values::sample_silence) {
		return;
	}

	// calculate gain ratio
	types::sample gain = values::sample_line_level / max;

	// apply gain
	channel_gain_apply(channel, gain);
}

void cdsp::sample_buffer::normalize() {
	// find max
	types::sample current;
	types::sample max = values::sample_infinity_n;
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		const types::sample* channel_buffer = channel_pointer_read(channel);

		types::disc_32_u samples_remaining = channel_buffer_length;
		while (samples_remaining--) {
			current = *channel_buffer++;
			if (current > max) {
				max = current;
			}
		}
	}

	// protect against divide by zero
	if (max == values::sample_silence) {
		return;
	}

	// calculate gain ratio
	types::sample gain = values::sample_line_level / max;

	// apply gain to all channels
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		channel_gain_apply(channel, gain);
	}
}

void cdsp::sample_buffer::normalize_independent() {
	for (types::disc_32_u channel = 0; channel < channels_num; channel++) {
		channel_normalize(channel);
	}
}