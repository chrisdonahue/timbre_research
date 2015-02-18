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

		// block parameters
		template<typename T> void parameter_rate_block_add(std::string parameter_specifier, T value_initial, T value_min, T value_max) {
			throw exceptions::template_specialization("cdsp::primitive::base: parameter_block_add called on unexpected type");
		};
		template<> void parameter_rate_block_add(std::string parameter_specifier, types::disc_32 value_initial, types::disc_32 value_min, types::disc_32 value_max) {
			parameter::rate_block<types::disc_32> myp(value_initial, value_min, value_max);
			//parameters_rate_block_disc_32.insert(std::make_pair(parameter_specifier,);
		};

		// real-time parameters

	private:
		std::unordered_map<std::string, parameter::rate_block<types::disc_32>&> parameters_rate_block_disc_32;
		std::unordered_map<std::string, parameter::rate_block<types::cont_32>&> parameters_rate_block_cont_32;
		std::unordered_map<std::string, parameter::ramp_linear&> parameters_rate_audio_ramp_linear;
		std::unordered_map<std::string, parameter::signal&> parameters_rate_audio_signal;
	};
}}

#endif