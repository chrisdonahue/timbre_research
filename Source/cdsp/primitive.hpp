#ifndef CDSP_PRIMITIVE
#define CDSP_PRIMITIVE

#include "parameter.hpp"
#include "types.hpp"

namespace cdsp {
	class primitive {
	public:
		virtual void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		virtual void release();
		virtual void perform(types::disc_32_u block_size, types::cont_32** channels_input, types::cont_32** channels_output) = 0;

	private:
		types::disc_32_u channels_input_num;
		types::disc_32_u channels_output_num;
	};
}

#endif