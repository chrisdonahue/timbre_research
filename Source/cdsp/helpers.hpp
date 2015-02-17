#ifndef CDSP_HELPERS
#define CDSP_HELPERS

#include <map>
#include <math.h>

#include "exceptions.hpp"
#include "types.hpp"
#include "values.hpp"

namespace cdsp { namespace helpers {
	// powers of two
	extern types::disc_32_u two_to_n(types::disc_32_u n);
	extern types::boolean is_power_of_two(types::disc_32_u n);

	// wavetable helpers
	extern void sine_sum(std::map<types::cont_32, types::cont_32> partials, types::disc_32_u buffer_length, types::sample* buffer);
}}

#endif