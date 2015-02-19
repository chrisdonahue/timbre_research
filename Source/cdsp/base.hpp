#ifndef CDSP_BASE
#define CDSP_BASE

#include "sample_buffer.hpp"
#include "types.hpp"

namespace cdsp {
	class base {
	protected:
		types::string identifier;
	};

	class dsp : public base {
	public:
		virtual void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			sample_rate = _sample_rate;
			block_size = _block_size;
		}
		virtual void release();

		virtual void perform(sample_buffer& buffer) = 0;
	protected:
		types::cont_64 sample_rate;
		types::disc_32_u block_size;
	}
}

#endif