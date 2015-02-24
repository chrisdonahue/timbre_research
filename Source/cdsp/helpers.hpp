#ifndef CDSP_HELPERS
#define CDSP_HELPERS

#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <set>
#include <tuple>
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
	extern void sine_sum(std::set<std::tuple<types::cont_64, types::cont_64, types::cont_64> > partials, types::disc_32_u buffer_length, types::sample* buffer);

	// range mappers
	template <typename T> void range_map_linear(T w, T x, T y, T z, T& m, T& b) {
		m = (z - y) / (x - w);
		b = (y - (w * m));
	};

	// memoized divide
#ifdef CDSP_MEMORY_HIGH
	static std::unordered_map<types::cont_64, types::cont_32> inverse_memoize;
	extern types::cont_32 inverse_memoized(types::cont_64 x);
#endif

	namespace io {
		extern void wav_file_save(std::string file_path, types::cont_64 sample_rate, types::disc_32_u sample_bit_depth, sample_buffer& sample_buffer);
	}
}}

#endif