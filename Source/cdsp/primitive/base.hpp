#ifndef CDSP_BASE
#define CDSP_BASE

#include <unordered_map>
#include <utility>

#include "../exceptions.hpp"
#include "../parameter.hpp"
#include "../sample_buffer.hpp"
#include "../types.hpp"

namespace cdsp { namespace primitive {
	class base {
	public:
		base();
		~base();

		// dsp 
		virtual void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		virtual void release();
		virtual void perform(sample_buffer& buffer) = 0;

	protected:
		types::disc_32_u channels_input_num;
		types::disc_32_u channels_output_num;

		/*
		// block-time parameter add
		template<typename T> void parameter_rate_block_add(std::string parameter_specifier, T value_initial, T value_min, T value_max) {
			throw exceptions::template_specialization("cdsp::primitive::base: parameter_block_add called on unexpected type");
		};
		template<> void parameter_rate_block_add(std::string parameter_specifier, types::disc_32 value_initial, types::disc_32 value_min, types::disc_32 value_max) {
			parameters_rate_block_disc_32.insert(std::make_pair(parameter_specifier, parameter::rate_block<types::disc_32>(value_initial, value_min, value_max)));
		};
		template<> void parameter_rate_block_add(std::string parameter_specifier, types::cont_32 value_initial, types::cont_32 value_min, types::cont_32 value_max) {
			parameters_rate_block_cont_32.insert(std::make_pair(parameter_specifier, parameter::rate_block<types::cont_32>(value_initial, value_min, value_max)));
		};

		// real-time parameter add
		void parameter_rate_audio_add(std::string parameter_specifier, types::sample value_initial, types::sample value_min, types::sample value_max) {
			parameters_rate_audio_ramp_linear.insert(std::make_pair(parameter_specifier, parameter::ramp_linear(value_initial, value_min, value_max)));
		};

		// TODO: getters and setters

		// plug and unplug signals into real-time parameters
		void parameter_rate_audio_unplug(std::string parameter_specifier) {

		};

		void parameter_rate_audio_plug(std::string parameter_specifier, const types::sample* buffer) {
			auto it = parameters_rate_audio_ramp_linear.find(parameter_specifier);
			if (it == parameters_rate_audio_ramp_linear.end()) {
				auto it2 = parameters_rate_audio_signal.find(parameter_specifier);
				if (it2 == parameters_rate_audio_signal.end()) {
					// TODO raise error
				}
				else {
					*it2->second.value_buffer_set(buffer);
				}
			}
			else {
				types::sample value_min = it->second.value_min_get();
				types::sample value_max = it->second.value_min_get();
				parameters_rate_audio_ramp_linear.erase(parameter_specifier);
				parameter::signal signal(value_min, value_max);
				signal.value_buffer_set(buffer);
				parameters_rate_audio_signal.insert(std::make_pair(parameter_specifier, signal));
			}
		};*/

	private:
		std::unordered_map<std::string, parameter::rate_block<types::disc_32>*> parameters_rate_block_disc_32;
		std::unordered_map<std::string, parameter::rate_block<types::cont_32>*> parameters_rate_block_cont_32;
		std::unordered_map<std::string, parameter::ramp_linear*> parameters_rate_audio_ramp_linear;
		std::unordered_map<std::string, parameter::signal*> parameters_rate_audio_signal;
	};
}}

#endif