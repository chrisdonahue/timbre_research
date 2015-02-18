#ifndef CDSP_SAMPLE_BUFFER
#define CDSP_SAMPLE_BUFFER

#include <cstdlib>

#include "types.hpp"
#include "values.hpp"

namespace cdsp {
	class sample_buffer {
	public:
		sample_buffer(types::disc_32_u channels_num, types::disc_32_u channel_buffer_length);
		~sample_buffer();

		// meta data accessors
		types::disc_32_u channels_num_get();
		types::disc_32_u channel_buffer_length_get();
		types::disc_32_u buffer_length_get();
		types::size buffer_size_get();

		// read/write pointer accessors
		const types::sample* channel_pointer_read(types::disc_32_u channel);
		types::sample* channel_pointer_write(types::disc_32_u channel);

		// clear
		void channel_clear(types::disc_32_u channel);
		void clear();
		
		// gain
		void channel_gain_apply(types::disc_32_u channel, types::sample gain);
		void gain_apply(types::sample gain);
		
		// dc offset
		void channel_dc_filter(types::disc_32_u channel, types::sample r=values::sample_dc_block_r);
		void dc_filter();

		// normalize
		void channel_normalize(types::disc_32_u channel);
		void normalize();
		void normalize_independent();

	private:
		types::disc_32_u channels_num;
		types::disc_32_u channel_buffer_length;
		types::disc_32_u buffer_length;
		types::sample* buffer;
	};
}

#endif