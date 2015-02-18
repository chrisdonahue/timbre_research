#ifndef CDSP_PARAMETER
#define CDSP_PARAMETER

#include <limits>
#include <unordered_map>

#include "helpers.hpp"
#include "types.hpp"

namespace cdsp { namespace parameter {
	template <typename T>
	class base {
	public:
		base(T value_initial) {
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
			value = (_value_min + _value_max) / static_cast<T>(2);
			value_range_valid = static_cast<types::boolean>(true);
			value_min = _value_min;
			value_max = _value_max;
		};

		base(T value_initial, T _value_min, T _value_max) {
			value = value_initial;
			value_range_valid = static_cast<types::boolean>(true);
			value_min = _value_min;
			value_max = _value_max;
		};
		
		virtual void prepare(types::cont_64 sample_rate, types::disc_32_u block_size) {};
		virtual void release() {};

		T value_get() {
			return value;
		};

		T value_set(T _value) {
			value = _value;
		};

	protected:
		T value;
		types::boolean value_range_valid;
		T value_min;
		T value_max;
	};

	template <typename T>
	class rate_block : public base<T> {
	public:
		using base::base;
	};

	class rate_audio : public base<types::sample> {
	public:
		using base::base;

		virtual void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			sample_rate = _sample_rate;
			block_size = _block_size;
		};

		virtual void release() {};

		virtual const types::sample* value_buffer_get(types::disc_32_u block_size_leq) = 0;

	protected:
		types::cont_64 sample_rate;
		types::disc_32_u block_size;
	};

	class ramp_linear : public rate_audio {
	public:
		using rate_audio::rate_audio;

		void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			rate_audio::prepare(_sample_rate, _block_size);
			types::cont_64 block_size = static_cast<types::cont_64>(_block_size);
#ifdef CDSP_MEMORY_HIGH
			block_size_inverse = helpers::inverse_memoized(block_size);
#else
			block_size_inverse = 1.0 / block_size;
#endif
			buffer.resize(1, _block_size);
			dezipper_buffer = buffer.channel_pointer_write(0);
		}

		void release() {
			buffer.resize(0, 0);
		};

		const types::sample* value_buffer_get(types::disc_32_u block_size_leq) {
			types::sample* buffer = dezipper_buffer;
			types::disc_32_u buffer_samples_remaining = block_size_leq;

			// dezipper
			types::disc_32_u dezipper_samples_completed;
			types::disc_32_u dezipper_samples_remaining;
			types::sample dezipper_increment;
			types::sample value_current = value;
			value_dezipper_start(dezipper_samples_completed, dezipper_increment);
			dezipper_samples_completed = dezipper_samples_completed > buffer_samples_remaining ? buffer_samples_remaining : dezipper_samples_completed;
			dezipper_samples_remaining = dezipper_samples_completed;
			while (dezipper_samples_remaining--) {
				*(buffer++) = value;
				value += dezipper_increment;
				buffer_samples_remaining--;
			}
			value_dezipper_end(dezipper_samples_completed, value_current);

			// fill rest of buffer
			while (buffer_samples_remaining--) {
				*(buffer++) = value;
			}

			// return dezippered buffer
			return const_cast<types::sample*>(dezipper_buffer);
		};

		void value_next_set(types::sample value_next, types::cont_64 delay_s) {
			value_next = value;
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

		void value_next_set(types::sample value_next) {
			value_next = value;
			types::cont_64 value_difference = static_cast<types::cont_64>(value_next - value);
			dezipper_samples_num = block_size;
			dezipper_increment = static_cast<types::sample>(block_size_inverse * value_difference);
		};

	private:
		// TODO: inline these
		void value_dezipper_start(types::disc_32_u& _dezipper_samples_num, types::sample& _dezipper_increment) {
			_dezipper_samples_num = dezipper_samples_num;
			_dezipper_increment = dezipper_increment;
		};

		void value_dezipper_end(types::disc_32_u dezipper_samples_completed, types::sample _value) {
			value = _value;
			dezipper_samples_num -= dezipper_samples_completed;
			if (dezipper_samples_num <= 0) {
				value = value_next;
				dezipper_samples_num = 0;
				dezipper_increment = values::sample_silence;
			}
		};

		types::cont_64 block_size_inverse;

		sample_buffer buffer;
		types::sample value_next;

		types::sample* dezipper_buffer;
		types::disc_32_u dezipper_samples_num;
		types::sample dezipper_increment;
	};

	class signal : public rate_audio {
	public:
		using rate_audio::rate_audio;

		void value_buffer_set(const types::sample* _value_buffer) {
			value_buffer = _value_buffer;
		};

		const types::sample* value_buffer_get() {
			return value_buffer;
		};

	private:
		const types::sample* value_buffer;
	};
}}

#endif