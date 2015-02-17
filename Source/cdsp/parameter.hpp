#ifndef CDSP_PARAMETER
#define CDSP_PARAMETER

#include "types.hpp"

namespace cdsp {
	template <typename T> class parameter {
	public:
		parameter(T value_initial) {
			value = value_initial;
		};

		~parameter() {};

		T value_get() {
			return value;
		};

		T value_next_get() {
			return value;
		};

		void value_next_set(T value_next_new) {
			value = value_next_new;
		};

	protected:
		T value;
	};

	template <typename T> class parameter_dezippered : public parameter < T > {
	public:
		parameter_dezippered(T value_initial) : parameter(value_initial) {
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