#ifndef CDSP_PARAMETER
#define CDSP_PARAMETER

#include <limits>
#include <unordered_map>

#include "base.hpp"
#include "helpers.hpp"
#include "types.hpp"
#include "values.hpp"

namespace cdsp { namespace parameter {
	template <typename T>
	class base {
	public:
		base() {
			value_valid = false;
			value_range_valid = false;
		};

		base(T value_initial) {
			value_valid = true;
			value = value_initial;
			value_range_valid = static_cast<types::boolean>(false);
#ifdef CDSP_WIN32
			__pragma(warning(push))
				__pragma(warning(disable:4127))
#endif
				if (std::numeric_limits<T>::has_infinity) {
					value_max = std::numeric_limits<T>::infinity();
					value_min = static_cast<T>(-1.0) * value_max;
				}
				else {
					value_max = std::numeric_limits<T>::min();
					value_max = std::numeric_limits<T>::max();
				}
#ifdef CDSP_WIN32
				__pragma(warning(pop))
#endif
		};

		base(T _value_min, T _value_max) {
			value_valid = true;
			value = (_value_min + _value_max) / static_cast<T>(2);
			value_range_valid = static_cast<types::boolean>(true);
			value_min = _value_min;
			value_max = _value_max;
		};

		base(T value_initial, T _value_min, T _value_max) {
			value_valid = (value_initial >= _value_min) && (value_initial <= _value_max);
			value = value_initial;
			value_range_valid = static_cast<types::boolean>(true);
			value_min = _value_min;
			value_max = _value_max;
		};

		types::boolean value_valid_get() {
			return value_valid;
		};

		void value_valid_set(types::boolean _value_valid) {
			value_valid = _value_valid;
		};

		T value_get() {
			return value;
		};

		void value_set(T _value) {
			value = _value;
		};

		T value_min_get() {
			return value_min;
		};

		T value_max_get() {
			return value_max;
		};

	protected:
		types::boolean value_valid;
		T value;
		types::boolean value_range_valid;
		T value_min;
		T value_max;
	};

	template <typename T>
	class rate_block : public parameter::base<T> {
	public:
		rate_block() : parameter::base<T>() {};
		rate_block(T value_initial) : parameter::base<T>(value_initial) {};
		rate_block(T value_min, T value_max) : parameter::base<T>(value_min, value_max) {};
		rate_block(T value_initial, T value_min, T value_max) : parameter::base<T>(value_initial, value_min, value_max) {};
	};

	class rate_audio : public base<types::sample>, public dsp {
	public:
		rate_audio() : parameter::base<types::sample>() {};
		rate_audio(types::sample value_initial) : parameter::base<types::sample>(value_initial), dsp() {};
		rate_audio(types::sample value_min, types::sample value_max) : parameter::base<types::sample>(value_min, value_max), dsp() {};
		rate_audio(types::sample value_initial, types::sample value_min, types::sample value_max) : parameter::base<types::sample>(value_initial, value_min, value_max), dsp() {};
	};

	class ramp_linear : public rate_audio {
	public:
		ramp_linear(): rate_audio() {};
		ramp_linear(types::sample value_initial) : rate_audio(value_initial), block_size_inverse(values::nan_64), value_next(value), dezipper_samples_num(0), dezipper_increment(values::sample_silence) {};
		ramp_linear(types::sample value_min, types::sample value_max) : rate_audio(value_min, value_max), block_size_inverse(values::nan_64), value_next(value), dezipper_samples_num(0), dezipper_increment(values::sample_silence) {};
		ramp_linear(types::sample value_initial, types::sample value_min, types::sample value_max) : rate_audio(value_initial, value_min, value_max), block_size_inverse(values::nan_64), value_next(value), dezipper_samples_num(0), dezipper_increment(values::sample_silence) {};

		void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			rate_audio::prepare(_sample_rate, _block_size);
			types::cont_64 block_size = static_cast<types::cont_64>(_block_size);
#ifdef CDSP_MEMORY_HIGH
			block_size_inverse = helpers::inverse_memoized(block_size);
#else
			block_size_inverse = 1.0 / block_size;
#endif
		};

		void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel offset_channel = 0, types::disc_32_u offset_sample = 0) {
			rate_audio::perform(buffer, block_size_leq, offset_channel, offset_sample);
		};

		void value_set(types::sample _value) {
			value = _value;
			value_next = _value;
			dezipper_samples_num = 0;
			dezipper_increment = values::sample_silence;
		};

		void value_next_set(types::sample _value_next, types::cont_64 delay_s) {
#ifdef CDSP_DEBUG
			if (delay_s <= values::zero_64) {
				throw exceptions::runtime("cdsp::parameter::ramp_linear: value_next_set called with a negative delay_s");
			}
			else if (delay_s == values::zero_64) {
				return;
			}
			if (_value_next == value) {
				return;
			}
#endif

			value_next = _value_next;
			types::cont_64 value_difference = static_cast<types::cont_64>(value_next - value);
			types::cont_64 ramp_length_samples = sample_rate * delay_s;
#ifdef CDSP_MEMORY_HIGH
			types::cont_64 inverse = helpers::inverse_memoized(ramp_length_samples);
#else
			types::cont_64 inverse = 1.0 / ramp_length_samples;
#endif
			dezipper_samples_num = static_cast<types::disc_32_u>(ramp_length_samples);
			dezipper_increment = static_cast<types::sample>(inverse * value_difference);
		};

		void value_next_set(types::sample _value_next) {
			if (_value_next == value) {
				return;
			}

			value_next = _value_next;
			types::cont_64 value_difference = static_cast<types::cont_64>(value_next - value);
			dezipper_samples_num = block_size;
			dezipper_increment = static_cast<types::sample>(block_size_inverse * value_difference);
		};

	protected:
		void _value_dezipper_start(types::disc_32_u& _dezipper_samples_num, types::sample& _dezipper_increment) {
			_dezipper_samples_num = dezipper_samples_num;
			_dezipper_increment = dezipper_increment;
		};

		void _value_dezipper_end(types::disc_32_u dezipper_samples_completed, types::sample _value) {
			value = _value;
			dezipper_samples_num -= dezipper_samples_completed;
			if (dezipper_samples_num <= 0) {
				value = value_next;
				dezipper_samples_num = 0;
				dezipper_increment = values::sample_silence;
			}
		};

		types::cont_64 block_size_inverse;

		types::sample value_next;

		types::disc_32_u dezipper_samples_num;
		types::sample dezipper_increment;
	};

	class ramp_linear_manual : public ramp_linear {
	public:
		ramp_linear_manual(): ramp_linear() {};
		ramp_linear_manual(types::sample value_initial) : ramp_linear(value_initial) {};
		ramp_linear_manual(types::sample value_min, types::sample value_max) : ramp_linear(value_min, value_max) {};
		ramp_linear_manual(types::sample value_initial, types::sample value_min, types::sample value_max) : ramp_linear(value_initial, value_min, value_max) {};

		void value_dezipper_start(types::disc_32_u& _dezipper_samples_num, types::sample& _dezipper_increment) {
			_value_dezipper_start(_dezipper_samples_num, _dezipper_increment);
		};

		void value_dezipper_end(types::disc_32_u dezipper_samples_completed, types::sample _value) {
			_value_dezipper_end(dezipper_samples_completed, _value);
		};
	};

	class ramp_linear_automatic : public ramp_linear {
	public:
		ramp_linear_automatic(): ramp_linear() {};
		ramp_linear_automatic(types::sample value_initial) : ramp_linear(value_initial) {};
		ramp_linear_automatic(types::sample value_min, types::sample value_max) : ramp_linear(value_min, value_max) {};
		ramp_linear_automatic(types::sample value_initial, types::sample value_min, types::sample value_max) : ramp_linear(value_initial, value_min, value_max) {};

		void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			ramp_linear::prepare(_sample_rate, _block_size);
			buffer.resize(1, _block_size);
			dezipper_buffer = buffer.channel_pointer_write(0);
		};

		void release() {
			ramp_linear::release();
			buffer.resize(0, 0);
		};

		void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel offset_channel = 0, types::disc_32_u offset_sample = 0) {
			ramp_linear::perform(buffer, block_size_leq, offset_channel, offset_sample);

			types::sample* buffer_output = buffer.channel_pointer_write(offset_channel, offset_sample);
			types::disc_32_u buffer_samples_remaining = block_size_leq;

			// dezipper
			types::disc_32_u dezipper_samples_completed;
			types::disc_32_u dezipper_samples_remaining;
			types::sample _dezipper_increment;
			types::sample value_current = value;
			_value_dezipper_start(dezipper_samples_completed, _dezipper_increment);
			dezipper_samples_completed = dezipper_samples_completed > buffer_samples_remaining ? buffer_samples_remaining : dezipper_samples_completed;
			dezipper_samples_remaining = dezipper_samples_completed;
			while (dezipper_samples_remaining--) {
				*(buffer_output++) = value;
				value += _dezipper_increment;
				buffer_samples_remaining--;
			}
			_value_dezipper_end(dezipper_samples_completed, value_current);

			// fill rest of buffer
			while (buffer_samples_remaining--) {
				*(buffer_output++) = value;
			}
		};

	private:
		sample_buffer buffer;

		types::sample* dezipper_buffer;
	};

	class signal : public rate_audio {
	public:
		signal(types::channel _channel) : rate_audio() {
			channel = _channel;
			range_map = false;
			parameter_m = values::sample_line_level;
			parameter_b = values::sample_silence;
		};
		signal(types::channel _channel, types::sample signal_min, types::sample signal_max, types::sample parameter_min, types::sample parameter_max) : rate_audio(parameter_min, parameter_max) {
			channel = _channel;
			if (signal_min == parameter_min && signal_max == parameter_max) {
				range_map = false;
				parameter_m = values::sample_line_level;
				parameter_b = values::sample_silence;
			}
			else {
				range_map = true;
				helpers::range_map_linear(signal_min, signal_max, parameter_min, parameter_max, parameter_m, parameter_b);
			}
		};

		void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel offset_channel = 0, types::disc_32_u offset_sample = 0) {
			rate_audio::perform(buffer, block_size_leq, offset_channel, offset_sample);

			if (range_map) {
				types::sample* output = buffer.channel_pointer_write(channel, offset_sample);
				while (block_size_leq--) {
					*(output) = ((*output) * parameter_m) + parameter_b;
					output++;
				}
			}
		};

		types::channel channel_get() {
			return channel;
		};

		void channel_set(types::disc_32_u _channel) {
			channel = _channel;
		};

	private:
		types::channel channel;

		types::boolean range_map;
		types::sample parameter_m;
		types::sample parameter_b;
	};
}}

#endif