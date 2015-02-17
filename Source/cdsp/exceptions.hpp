#ifndef CDSP_EXCEPTIONS
#define CDSP_EXCEPTIONS

#include <exception>
#include <sstream>
#include <stdexcept>

namespace cdsp { namespace exceptions {
	class runtime : public std::runtime_error {
	public:
		runtime(const std::string& msg) : std::runtime_error(msg) {};
	};

	class template_specialization : public std::runtime_error {
	public:
		template_specialization(const std::string& msg) : std::runtime_error(msg) {};
	};
}}

#endif