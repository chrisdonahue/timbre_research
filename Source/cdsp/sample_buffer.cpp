#include "sample_buffer.hpp"

cdsp::sample_buffer::sample_buffer(types::disc_32_u _channels_num, types::disc_32_u _channel_buffer_length) {
	channels_num = _channels_num;
	channel_buffer_length = _channel_buffer_length;
	buffer_length = channels_num * channel_buffer_length;
	buffer = static_cast<types::sample*>(malloc(sizeof(types::sample) * buffer_length));
}

cdsp::sample_buffer::~sample_buffer() {
	free(buffer);
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

const cdsp::types::sample* cdsp::sample_buffer::channel_pointer_read(types::disc_32_u channel) {
	return static_cast<const types::sample*>(buffer + (channel * buffer_length));
}

cdsp::types::sample* cdsp::sample_buffer::channel_pointer_write(types::disc_32_u channel) {
	return buffer + (channel * buffer_length);
}

