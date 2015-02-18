#ifndef CDSP_OSCILLATOR_TABLE_OSCILLATOR
#define CDSP_OSCILLATOR_TABLE_OSCILLATOR

#include <math.h>

#include "../../helpers.hpp"
#include "../base.hpp"

namespace cdsp { namespace primitive { namespace oscillator {
	class table_interpolate_4 : public cdsp::primitive::base {
	public:
		table_interpolate_4();

		void perform(sample_buffer& buffer);

		void table_set(types::disc_32_u table_length, const types::sample* table);

	private:
		void parameters_add();

		types::disc_32_u table_length;
		types::disc_32_u table_mask;
		const types::sample* table;

		types::cont_64 phase;
	};
}}}

#endif