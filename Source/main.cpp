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
	types::disc_32_u output_buffer_length = 1024 * 16;
	sample_buffer output_buffer(1, output_buffer_length);
	output_buffer.clear();

	// prepare
	types::cont_64 sample_rate = 44100.0;
	types::disc_32_u block_size = 1024;
	oscillator.prepare(sample_rate, block_size);

	// perform
	oscillator.frequency_set(static_cast<types::sample>(0.01f));
	int i;
	for (i = 0; i < 7; i++) {
		oscillator.perform(output_buffer, block_size, 0, 0, block_size * i);
	}
	oscillator.frequency_set(static_cast<types::sample>(0.02f));
	for (; i < 16; i++) {
		oscillator.perform(output_buffer, block_size, 0, 0, block_size * i);
	}

	// release
	oscillator.release();

	// save
	helpers::io::wav_file_save("output.wav", sample_rate, 32, output_buffer);

    return 0;
}
