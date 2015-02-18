#include "../JuceLibraryCode/JuceHeader.h"

#include "cdsp/cdsp.hpp"

int main (int argc, char* argv[]) {
	argc;
	argv;

	using namespace cdsp;

	// create table oscillator
	primitive::oscillator::table_interpolate_4 oscillator;
	types::disc_32_u table_length = 1024;
	sample_buffer table(1, table_length);
	helpers::sine_sum(std::map<types::cont_32, types::cont_32>(), table_length, table.channel_pointer_write(0));
	oscillator.table_set(table_length, table.channel_pointer_read(0));

	// create output buffer
	types::disc_32_u output_buffer_length = 44100;
	sample_buffer output_buffer(1, output_buffer_length);

	// perform
	oscillator.parameter_set("frequency", 0.00249433106f, 0.0f);
	oscillator.perform(output_buffer);

	// save
	helpers::io::wav_file_save("output.wav", 44100, 32, output_buffer);

    return 0;
}
