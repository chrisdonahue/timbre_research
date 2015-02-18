#ifndef CDSP_PARAMETER
#define CDSP_PARAMETER

#include <limits>

#include "types.hpp"

namespace cdsp {
	template <typename T> class parameter {
	public:
		parameter(T value_initial) {
			value = value_initial;

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

		parameter(T _value_min, T _value_max) {
			value = (_value_min + _value_max) / dynamic_cast<T>(2.0);
			value_min = _value_min;
			value_max = _value_max;
		};

		parameter(T value_initial, T _value_min, T _value_max) {
			value = value_initial;
			value_min = _value_min;
			value_max = _value_max;
		};

		~parameter() {};

		T value_get() {
			return value;
		};

		void value_set(T value_new) {
			value = value_new;
		};

		void value_next_set(T value_next_new) {
			value = value_next_new;
		};

	private:
		T value;

		T value_min;
		T value_max;
	};

	template <typename T> class parameter_rate_block : public parameter < T > {
	public:
		parameter_rate_block(T value_initial) : parameter(value_initial) {
			value_next = value_initial;
		};

		T value_next_get() {
			return value_next;
		};

		void value_next_set(T value_next_new) {
			value_next = value_next_new;
		};

		void value_dezipper_start(types::cont_32 block_size_inverse, types::boolean& value_next_differs, types::cont_32& value_current, types::cont_32& value_increment) {
			if (value == value_next) {
				value_next_differs = false;
				value_increment = 0.0f;
			}
			else {
				value_next_differs = true;
				value_increment = block_size_inverse * static_cast<types::cont_32>(value_next - value);
			}
			value_current = value;
		};

		void value_dezipper_finish(T value_new) {
			value = value_new;
		};

	private:
		T value_next;
	};
}

#endif