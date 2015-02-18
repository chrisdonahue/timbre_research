#ifndef CDSP_SAMPLE_BUFFER
#define CDSP_SAMPLE_BUFFER

#include <cstdlib>

#include "types.hpp"

namespace cdsp {
	class sample_buffer {
	public:
		sample_buffer(types::disc_32_u channels_num, types::disc_32_u channel_buffer_length);
		~sample_buffer();

		types::disc_32_u channels_num_get();
		types::disc_32_u channel_buffer_length_get();
		types::disc_32_u buffer_length_get();
		types::size buffer_size_get();

		const types::sample* channel_pointer_read(types::disc_32_u channel);
		types::sample* channel_pointer_write(types::disc_32_u channel);

	private:
		types::disc_32_u channels_num;
		types::disc_32_u channel_buffer_length;
		types::disc_32_u buffer_length;
		types::sample* buffer;
	};
}

#endif