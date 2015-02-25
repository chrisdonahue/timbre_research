#ifndef CDSP_BASE
#define CDSP_BASE

#include "defines.hpp"
#include "exceptions.hpp"
#include "sample_buffer.hpp"
#include "types.hpp"

namespace cdsp {
	class base {
	protected:
		types::string identifier;
	};

	class dsp : public base {
	public:
		dsp() {
#ifdef CDSP_DEBUG
			prepared = false;
#endif
		};

		virtual void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			sample_rate = _sample_rate;
			block_size = _block_size;
#ifdef CDSP_DEBUG
			prepared = true;
#endif
		}
		virtual void release() {
#ifdef CDSP_DEBUG
			prepared = false;
#endif
		};
		virtual void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel offset_channel = 0, types::disc_32_u offset_sample = 0) = 0 {
			CDSP_UNUSED_PARAMETER(buffer);
			CDSP_UNUSED_PARAMETER(block_size_leq);
			CDSP_UNUSED_PARAMETER(offset_channel);
			CDSP_UNUSED_PARAMETER(offset_sample);

#ifdef CDSP_DEBUG_DSP
			if (!prepared) {
				throw exceptions::runtime("cdsp::dsp: perform called while not prepared");
			}
#endif
		};

	protected:
		types::cont_64 sample_rate;
		types::disc_32_u block_size;

	private:
#ifdef CDSP_DEBUG
		types::boolean prepared;
#endif
	};
}

#endif