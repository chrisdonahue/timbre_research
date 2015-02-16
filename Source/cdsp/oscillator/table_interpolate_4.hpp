#ifndef TABLE_OSCILLATOR
#define TABLE_OSCILLATOR

#include "../dsp_primitive.hpp"

namespace cdsp { namespace oscillator {
	class table_interpolate_4 {
	public:
		void prepare(double sample_rate, int block_size);
		void release();

		void perform(int block_size, float** channels_input, float** channels_output);

	private:
		int table_size;
		float* table;
	};
}}

#endif
