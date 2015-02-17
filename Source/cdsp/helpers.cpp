#include "helpers.hpp"

cdsp::types::disc_32_u cdsp::helpers::two_to_n(types::disc_32_u n) {
	if (n == 0) {
		return 1;
	}

	return 1 << n;
};

cdsp::types::boolean cdsp::helpers::is_power_of_two(types::disc_32_u n) {
	n;
	return true;
};

void cdsp::helpers::sine_sum(std::map<types::cont_32, types::cont_32> partials, types::disc_32_u buffer_length, types::sample* buffer) {
	if (buffer_length == 0) {
		throw exceptions::runtime("cdsp::helpers::sine_sum: buffer_length is 0");
	}

	// TODO: partials
	types::cont_64 index_value = 0.0;
	types::cont_64 index_increment = values::two_pi_64 / static_cast<types::cont_64>(buffer_length);
	for (types::disc_32_u i = 0; i < buffer_length; i++) {
		buffer[i] = sinf(static_cast<types::sample>(index_value));
		index_value += index_increment;
	}
}