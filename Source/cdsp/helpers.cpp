#include "helpers.hpp"

cdsp::types::disc_32_u cdsp::helpers::two_to_n(types::disc_32_u n) {
	if (n == 0) {
		return 1;
	}

	return 1 << n;
};

cdsp::types::boolean cdsp::helpers::is_power_of_two(types::disc_32_u n) {
	return true;
};

void cdsp::helpers::sine_sum(std::map<types::cont_32, types::cont_32> partials, types::disc_32_u buffer_length, types::sample* buffer) {
	for (int i = 0; i < buffer_length; i++) {
		buffer[i] = sinf(values::pi_const_32);
	}
}