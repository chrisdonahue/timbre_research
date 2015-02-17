#ifndef CDSP_PRIMITIVE
#define CDSP_PRIMITIVE

#include <map>
#include <utility>

#include "../exceptions.hpp"
#include "../parameter.hpp"
#include "../types.hpp"

namespace cdsp {
	class primitive {
	public:
		primitive();
		~primitive();

		// parameter get
		template<typename T> T parameter_get(const char* parameter_specifier) {
			throw exceptions::template_specialization("cdsp::primitive: parameter_get called on unexpected type");
		};
		template<> types::cont_32 parameter_get<types::cont_32>(const char* parameter_specifier) {
			auto it = parameters_cont_32.find(parameter_specifier);
			if (it == parameters_cont_32.end()) {
				throw exceptions::runtime("cdsp::primitive: parameter_get<types::cont_32> called on unexpected parameter specifier");
			}
			return (it->second).value_get();
		};

		// parameter set
		template<typename T> void parameter_set(const char* parameter_specifier, T value_new, types::cont_64 delay_ms) {
			delay_ms;
			throw exceptions::template_specialization("cdsp::primitive: parameter_set called on unexpected type");
		};
		template<> void parameter_set<types::cont_32>(const char* parameter_specifier, types::cont_32 value_new, types::cont_64 delay_ms) {
			delay_ms;
			auto it = parameters_cont_32.find(parameter_specifier);
			if (it == parameters_cont_32.end()) {
				throw exceptions::runtime("cdsp::primitive: parameter_set<types::cont_32> called on unexpected parameter specifier");
			}
			(it->second).value_next_set(value_new);
		};

		// dsp 
		virtual void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		virtual void release();
		virtual void perform(types::disc_32_u block_size, types::sample** channels_input, types::sample** channels_output) = 0;

	protected:
		// parameter add
		template<typename T> void parameter_add(const char* parameter_specifier, T value_initial, T value_min, T value_max) {
			value_min;
			value_max;
			throw exceptions::template_specialization("cdsp::primitive: parameter_add called on unexpected type");
		};
		template<> void parameter_add<types::cont_32>(const char* parameter_specifier, types::cont_32 value_initial, types::cont_32 value_min, types::cont_32 value_max) {
			value_min;
			value_max;
			auto it = parameters_cont_32.find(parameter_specifier);
			if (it != parameters_cont_32.end()) {
				throw exceptions::runtime("cdsp::primitive: parameter_add<types::cont_32> called for an already existing parameter specifier");
			}
			parameters_cont_32.insert(std::make_pair(std::string(parameter_specifier), parameter<types::cont_32>(value_initial)));
		};

		types::disc_32_u channels_input_num;
		types::disc_32_u channels_output_num;

	private:
		// parameters add
		void parameters_add();

		std::map<std::string, parameter<types::cont_32> > parameters_cont_32;
	};
}

#endif