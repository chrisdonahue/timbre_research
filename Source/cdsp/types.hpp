#ifndef CDSP_TYPES
#define CDSP_TYPES

#include <map>
#include <string>
#include <unordered_map>

#include "defines.hpp"

namespace cdsp { namespace types {
	typedef unsigned disc_32_u;
	typedef int disc_32;
	typedef float cont_32;
	typedef double cont_64;
	typedef bool boolean;
	typedef size_t size;
#ifdef CDSP_SAMPLE_64
	typedef cont_64 sample;
#else
	typedef cont_32 sample;
#endif
	typedef disc_32_u channel;
	typedef std::string string;
}}

#endif