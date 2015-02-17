#include "table_interpolate_4.hpp"

cdsp::oscillator::table_interpolate_4::table_interpolate_4() :
	table_size(0),
	table_mask(0),
	table(nullptr),
	phase(0.0)
{
};

void cdsp::oscillator::table_interpolate_4::prepare(types::cont_64 sample_rate, types::disc_32_u block_size) {
};

void cdsp::oscillator::table_interpolate_4::release() {
};

void cdsp::oscillator::table_interpolate_4::perform(types::disc_32_u block_size, types::cont_32** channels_input, types::cont_32** channels_output) {
		if (table == nullptr) {
			throw cdsp::exceptions::runtime("cdsp::oscillator::table_interpolate_4: perform called before set_table");
		}

		/*
		var frequency = buffer.channel_get(0);
		var output = buffer.channel_get(0);

		var table_length = this.table_length;
		var table_mask = this.table_mask;
		var table = this.table;
		var phase = this.phase;

		var frequency_current;
		var phase_increment;
		var phase_truncated;
		var fraction;
		var inm1;
		var in0;
		var inp1;
		var inp2;

		for (var i = 0; i < buffer_length; i++) {
			// find current frequency
			frequency_current = frequency[i];

			// calculate phase increment
			phase_increment = frequency_current * table_length;

			// truncate phase
			phase_truncated = Math.floor(phase);

			// calculate fractional position
			fraction = phase - phase_truncated;

			// calculate table offset
			inm1 = table[(phase_truncated - 1) & table_mask];
			in0 = table[phase_truncated & table_mask];
			inp1 = table[(phase_truncated + 1) & table_mask];
			inp2 = table[(phase_truncated + 2) & table_mask];

			// calculate output
			output[i] = in0 + 0.5 * fraction * (inp1 - inm1 + 
				fraction * (4.0 * inp1 + 2.0 * inm1 - 5.0 * in0 - inp2 +
				fraction * (3.0 * (in0 - inp1) - inm1 + inp2)));

			// add phase increment
			phase += phase_increment;
		}

		// prevent phase from overflowing
		while (phase > table_length) {
			phase = phase - table_length;
		}
		while (phase < 0.0) {
			phase = phase + table_length;
		}

		// store phase
		this.phase = phase;
		*/
};

void cdsp::oscillator::table_interpolate_4::table_set(types::disc_32_u table_size, types::cont_32* table) {
	table_size = table_size;
	table_mask = table_size - 1;
	table = table;
};