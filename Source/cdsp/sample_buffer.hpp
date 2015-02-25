#ifndef CDSP_SAMPLE_BUFFER
#define CDSP_SAMPLE_BUFFER

#include <cstdlib>

#include "types.hpp"
#include "values.hpp"

namespace cdsp {
	class sample_buffer {
	public:
		sample_buffer();
		sample_buffer(types::channel channels_num, types::disc_32_u channel_buffer_length);
		~sample_buffer();

		// resize
		void resize(types::channel _channels_num, types::disc_32_u _channel_buffer_length);

		// meta data accessors
		types::channel channels_num_get();
		types::disc_32_u channel_buffer_length_get();
		types::disc_32_u buffer_length_get();
		types::size buffer_size_get();

		// read/write pointer accessors
		const types::sample* channel_pointer_read(types::channel channel, types::disc_32_u offset = 0) const;
		types::sample* channel_pointer_write(types::channel channel, types::disc_32_u offset = 0);

		// clear
		void channel_clear(types::channel channel);
		void clear();
		
		// gain
		void channel_gain_apply(types::channel channel, types::sample gain);
		void gain_apply(types::sample gain);
		
		// dc offset
		void channel_dc_filter(types::channel channel, types::sample r = values::sample_dc_block_r);
		void dc_filter();

		// normalize
		void channel_normalize(types::channel channel);
		void normalize();
		void normalize_independent();

	private:
		// buffer memory management
		void buffer_reallocate();
		void buffer_free();

		types::channel channels_num;
		types::disc_32_u channel_buffer_length;
		types::disc_32_u buffer_length;
		types::sample* buffer;
	};
}

#endif