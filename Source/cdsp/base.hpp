#ifndef CDSP_BASE
#define CDSP_BASE

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
		virtual void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel channel_input = 0, types::channel channel_output = 0, types::disc_32_u offset = 0) = 0 {
			buffer;
			block_size_leq;
			channel_input;
			channel_output;
			offset;
#ifdef CDSP_DEBUG
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