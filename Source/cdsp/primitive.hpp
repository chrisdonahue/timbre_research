#ifndef PRIMITIVE
#define PRIMITIVE

namespace cdsp {
	class primitive {
	public:
		virtual void prepare(double sample_rate, int block_size);
		virtual void release();

		virtual void perform(int block_size, float** channels_input, float** channels_output) = 0;

	private:
		int channels_input_num;
		int channels_output_num;
	};
}

#endif
