#ifndef CDSP_HELPERS
#define CDSP_HELPERS

#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <unordered_map>

#include "defines.hpp"
#include "exceptions.hpp"
#include "sample_buffer.hpp"
#include "types.hpp"
#include "values.hpp"

namespace cdsp { namespace helpers {
	// powers of two
	extern types::disc_32_u two_to_n(types::disc_32_u n);
	extern types::boolean is_power_of_two(types::disc_32_u n);

	// wavetable helpers
	extern void sine_sum(std::map<types::cont_32, types::cont_32> partials, types::disc_32_u buffer_length, types::sample* buffer);

	// memoized divide
#ifdef CDSP_MEMORY_HIGH
	static std::unordered_map<types::cont_64, types::cont_32> inverse_memoize;
	extern types::cont_32 inverse_memoized(types::cont_64 x);
#endif

	namespace io {
		extern void wav_file_save(std::string file_path, types::disc_32_u sample_rate, types::disc_32_u sample_bit_depth, sample_buffer& sample_buffer);
	}
}}

#endif