#ifndef CDSP_OSCILLATOR_TABLE_OSCILLATOR
#define CDSP_OSCILLATOR_TABLE_OSCILLATOR

#include <math.h>

#include "../../helpers.hpp"
#include "../base.hpp"

namespace cdsp { namespace primitive { namespace oscillator {
	class table_interpolate_4 : public cdsp::primitive::base {
	public:
		table_interpolate_4();

		void table_set(types::disc_32_u _table_length, const types::sample* _table);
		void phase_set(types::cont_64 _phase);
		void frequency_set();

		void perform(sample_buffer& buffer);

	private:
		types::cont_64 phase;
		parameter::ramp_linear_automatic frequency;

		types::disc_32_u table_length;
		types::disc_32_u table_mask;
		const types::sample* table;
	};
}}}

#endif
