#ifndef CDSP_OSCILLATOR_TABLE_OSCILLATOR
#define CDSP_OSCILLATOR_TABLE_OSCILLATOR

#include <math.h>

#include "../../helpers.hpp"
#include "../primitive.hpp"

namespace cdsp { namespace oscillator {
	class table_interpolate_4 : public cdsp::primitive {
	public:
		table_interpolate_4();

		void perform(types::disc_32_u block_size, types::sample** channels_input, types::sample** channels_output);

		void table_set(types::disc_32_u table_size, types::sample* table);

	private:
		void parameters_add();

		types::disc_32_u table_length;
		types::disc_32_u table_mask;
		types::sample* table;

		types::cont_64 phase;
	};
}}

#endif
