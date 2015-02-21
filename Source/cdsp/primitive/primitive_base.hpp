#ifndef CDSP_PRIMITIVE_BASE
#define CDSP_PRIMITIVE_BASE

#include <set>
#include <unordered_map>
#include <utility>

#include "../exceptions.hpp"
#include "../parameter.hpp"
#include "../sample_buffer.hpp"
#include "../types.hpp"

namespace cdsp { namespace primitive {
	class base : public dsp {
	public:
		base() : dsp() {};

		// dsp
		virtual void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel channel_input = 0, types::channel channel_output = 0, types::disc_32_u offset = 0) = 0 {
			dsp::perform(buffer, block_size_leq, channel_input, channel_output, offset);
		};

		// plugs
		void parameter_plug(types::string parameter_specifier, parameter::signal* parameter_plug) {
			parameter_plugs.insert(std::make_pair(parameter_specifier, parameter_plug));
		};

		void parameter_unplug(types::string parameter_specifier) {
			parameter_plugs.erase(parameter_specifier);
		};

		const std::set<types::string>& parameter_plug_specifiers_get() {
			return const_cast<std::set<types::string>& >(parameter_plug_specifiers);
		};

	protected:
		types::disc_32_u channels_input_num;
		types::disc_32_u channels_output_num;

		void parameter_plug_register(types::string parameter_specifier) {
			// TODO: throw runtime error if already exists
			parameter_plug_specifiers.insert(parameter_specifier);
		};

		parameter::signal* parameter_plug_get(types::string parameter_specifier) {
			auto it = parameter_plugs.find(parameter_specifier);
			if (it != parameter_plugs.end()) {
				return it->second;
			}
			else {
				return nullptr;
			}
		};

	private:
		std::set<types::string> parameter_plug_specifiers;
		std::unordered_map<types::string, parameter::signal*> parameter_plugs;
	};
}}

#endif