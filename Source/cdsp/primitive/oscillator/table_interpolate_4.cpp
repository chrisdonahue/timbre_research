#include "table_interpolate_4.hpp"

cdsp::primitive::oscillator::table_interpolate_4::table_interpolate_4() :
	table_length(0),
	table_mask(0),
	table(nullptr),
	phase(0.0)
{
	// set num input and ouput channels
	channels_input_num = 0;
	channels_output_num = 1;

	// add parameters
	parameter_add("frequency", 0.0f, 0.0f, 1.0f);
};

void cdsp::primitive::oscillator::table_interpolate_4::perform(sample_buffer& buffer) {
		// check to make sure we have a table to interpolate
		if (table == nullptr) {
			throw cdsp::exceptions::runtime("cdsp::primitive::oscillator::table_interpolate_4: perform called before set_table");
		}

		// get parameter values
		types::cont_32 frequency = parameter_get<types::cont_32>("frequency");

		// create temporaries
		types::cont_32 frequency_current;
		types::cont_64 phase_increment;
		types::disc_32_u phase_truncated;
		types::cont_64 fraction;
		types::sample inm1;
		types::sample in0;
		types::sample inp1;
		types::sample inp2;

		// perform
		types::disc_32_u block_size = buffer.channel_buffer_length_get();
		for (types::disc_32_u i = 0; i < block_size; i++) {
			// find current frequency (TODO: dezippered)
			frequency_current = frequency;

			// calculate phase increment
			phase_increment = frequency_current * table_length;

			// truncate phase
			phase_truncated = static_cast<types::disc_32_u>(floor(phase));

			// calculate fractional position
			fraction = phase - (static_cast<types::cont_32>(phase_truncated));

			// calculate table offset
			inm1 = table[(phase_truncated - 1) & table_mask];
			in0 = table[phase_truncated & table_mask];
			inp1 = table[(phase_truncated + 1) & table_mask];
			inp2 = table[(phase_truncated + 2) & table_mask];

			// calculate interpolated output
			for (types::disc_32_u channel = 0; channel < channels_output_num; channel++) {
				buffer.channel_pointer_write(channel)[i] = static_cast<types::sample>(
					in0 + 0.5 * fraction * (inp1 - inm1 + 
					fraction * (4.0 * inp1 + 2.0 * inm1 - 5.0 * in0 - inp2 +
					fraction * (3.0 * (in0 - inp1) - inm1 + inp2)))
				);
			}

			// add phase increment
			phase += phase_increment;
		}

		// prevent phase from overflowing
		while (phase > table_length) {
			phase = phase - static_cast<types::cont_64>(table_length);
		}
		while (phase < 0.0) {
			phase = phase + static_cast<types::cont_64>(table_length);
		}
};

void cdsp::primitive::oscillator::table_interpolate_4::table_set(types::disc_32_u _table_length, const types::cont_32* _table) {
	if (!cdsp::helpers::is_power_of_two(_table_length)) {
		throw cdsp::exceptions::runtime("cdsp::primitive::oscillator::table_interpolate_4: table_set called with a table_size that was not a power of two");
	}

	table_length = _table_length;
	table_mask = table_length - 1;
	table = _table;
};