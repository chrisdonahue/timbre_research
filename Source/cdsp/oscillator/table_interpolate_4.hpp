#ifndef CDSP_OSCILLATOR_TABLE_OSCILLATOR
#define CDSP_OSCILLATOR_TABLE_OSCILLATOR

#include "../primitive.hpp"

namespace cdsp { namespace oscillator {
	class table_interpolate_4 : public cdsp::primitive {
	public:
		void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		void release();
		void perform(types::disc_32_u block_size, types::cont_32** channels_input, types::cont_32** channels_output);

	private:
		types::disc_32_u table_size;
		types::cont_32* table;
	};
}}

#endif
