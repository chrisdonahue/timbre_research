#include "../JuceLibraryCode/JuceHeader.h"

#include "cdsp/cdsp.hpp"

int main (int argc, char* argv[]) {
	argc;
	argv;

	using namespace cdsp;

	// create modulator
	primitive::oscillator::table_interpolate_4 modulator;
	types::disc_32_u table_length = 1024;
	sample_buffer table(1, table_length);
	helpers::sine_sum(std::map<types::cont_32, types::cont_32>(), table_length, table.channel_pointer_write(0));
	modulator.table_set(table_length, table.channel_pointer_read(0));

	// create carrier
	primitive::oscillator::table_interpolate_4 carrier;
	carrier.table_set(table_length, table.channel_pointer_read(0));

	// create output buffer
	types::disc_32_u output_buffer_length = 1024 * 16;
	sample_buffer output_buffer(1, output_buffer_length);
	output_buffer.clear();

	// connect
	parameter::signal fm(-1.0f, 1.0f);
	fm.buffer_set(const_cast<sample_buffer*>(&output_buffer));
	carrier.parameter_plug("frequency", &fm);

	// prepare
	types::cont_64 sample_rate = 44100.0;
	types::disc_32_u block_size = 1024;
	modulator.prepare(sample_rate, block_size);
	carrier.prepare(sample_rate, block_size);

	// perform
	modulator.frequency_set(static_cast<types::sample>(0.00002267573f));
	carrier.frequency_set(static_cast<types::sample>(0.01f));
	int i;
	for (i = 0; i < 7; i++) {
		modulator.perform(output_buffer, block_size, 0, 0, block_size * i);
		carrier.perform(output_buffer, block_size, 0, 0, block_size * i);
	}
	for (; i < 16; i++) {
		modulator.perform(output_buffer, block_size, 0, 0, block_size * i);
		carrier.perform(output_buffer, block_size, 0, 0, block_size * i);
	}

	// release
	carrier.release();

	// save
	helpers::io::wav_file_save("output.wav", sample_rate, 32, output_buffer);

    return 0;
}
