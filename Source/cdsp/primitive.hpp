#ifndef CDSP_PRIMITIVE
#define CDSP_PRIMITIVE

#include <map>

#include "exceptions.hpp"
#include "parameter.hpp"
#include "types.hpp"

namespace cdsp {
	class primitive {
	public:
		enum parameters {
			enum_count
		};

		// parameter get
		template<typename T> parameter<T> parameter_get(types::disc_32_u parameter_specifier) {
			throw exceptions::template_specialization("cdsp::primitive: parameter_get called on unexpected type");
		};
		template<> parameter<types::disc_32> parameter_get<types::disc_32>(types::disc_32_u parameter_specifier) {
		};
		template<> parameter<types::cont_32> parameter_get<types::cont_32>(types::disc_32_u parameter_specifier) {
		};

		// parameter set
		template<typename T> void parameter_set(types::disc_32_u parameter_specifier, T value_new, types::cont_64 delay_ms) {
			throw exceptions::template_specialization("cdsp::primitive: parameter_set called on unexpected type");
		};
		template<> void parameter_set<types::disc_32>(types::disc_32_u parameter_specifier, types::disc_32 value_new, types::cont_64 delay_ms) {
		};
		template<> void parameter_set<types::cont_32>(types::disc_32_u parameter_specifier, types::cont_32 value_new, types::cont_64 delay_ms) {
		};

		// dsp 
		virtual void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		virtual void release();
		virtual void perform(types::disc_32_u block_size, types::cont_32** channels_input, types::cont_32** channels_output) = 0;

	private:
		types::disc_32_u channels_input_num;
		types::disc_32_u channels_output_num;

		std::map<std::string, parameter<types::disc_32>& > parameters_disc_32;
		std::map<std::string, parameter<types::cont_32>& > parameters_cont_32;
	};
}

#endif