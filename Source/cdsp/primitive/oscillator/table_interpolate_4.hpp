#ifndef CDSP_OSCILLATOR_TABLE_OSCILLATOR
#define CDSP_OSCILLATOR_TABLE_OSCILLATOR

#include <math.h>

#include "../../helpers.hpp"
#include "../primitive_base.hpp"

namespace cdsp { namespace primitive { namespace oscillator {
	class table_interpolate_4 : public primitive::base {
	public:
		table_interpolate_4();

		void prepare(types::cont_64 _sample_rate, types::disc_32_u _block_size) {
			primitive::base::prepare(_sample_rate, _block_size);
			frequency.prepare(_sample_rate, _block_size);
		}

		void table_set(types::disc_32_u _table_length, const types::sample* _table);
		void phase_set(types::cont_64 _phase);
		void frequency_set(types::sample frequency);

		void perform(sample_buffer& buffer, types::disc_32_u block_size_leq, types::channel channel_input = 0, types::channel channel_output = 0, types::disc_32_u offset = 0);

	private:
		types::cont_64 phase;
		parameter::ramp_linear_automatic frequency;

		types::disc_32_u table_length;
		types::disc_32_u table_mask;
		const types::sample* table;
	};
}}}

#endif
