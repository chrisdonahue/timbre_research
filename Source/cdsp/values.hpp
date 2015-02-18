#ifndef CDSP_VALUES
#define CDSP_VALUES

#include <limits>

#include "defines.hpp"
#include "types.hpp"

namespace cdsp { namespace values {
	const types::cont_64 pi_64				= 3.1415926535897932384626433832795028841971693993751;
	const types::cont_32 pi_32				= 3.14159265358979f;
	const types::cont_64 two_pi_64			= 6.2831853071795864769252867665590057683943387987502;
	const types::cont_32 two_pi_32			= 6.283185307179586f;

#ifdef CDSP_SAMPLE_32
	const types::sample sample_silence		= static_cast<types::sample>(0.0f);
	const types::sample sample_line_level_n	= static_cast<types::sample>(-1.0f);
	const types::sample sample_line_level	= static_cast<types::sample>(1.0f);
	const types::sample sample_infinity_n	= -1.0f * std::numeric_limits<types::sample>::infinity();
	const types::sample sample_infinity		= std::numeric_limits<types::sample>::infinity();

	const types::sample sample_dc_block_r	= static_cast<types::sample>(0.995f);
#elif CDSP_SAMPLE_64
	const types::sample sample_silence		= static_cast<types::sample>(0.0);
	const types::sample sample_line_level_n = static_cast<types::sample>(-1.0);
	const types::sample sample_line_level	= static_cast<types::sample>(1.0);
	const types::sample sample_infinity_n	= -1.0 * std::numeric_limits<types::sample>::infinity();
	const types::sample sample_infinity		= std::numeric_limits<types::sample>::infinity();

	const types::sample sample_dc_block_r	= static_cast<types::sample>(0.995);
#endif
}}

#endif