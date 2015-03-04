#include "../JuceLibraryCode/JuceHeader.h"

#include "cdsp/cdsp.hpp"

int main (int argc, char* argv[]) {
	argc;
	argv;

	using namespace cdsp;

	// create modulator
	primitives::oscillators::table_interpolate_4 modulator;
	types::disc_32_u table_length = 1024;
	sample_buffer table(1, table_length);
	helpers::generators::cosine(table_length, table.channel_pointer_write(0));
	modulator.table_set(table_length, table.channel_pointer_read(0));

	// create carrier
	primitives::oscillators::table_interpolate_4 carrier;
	carrier.table_set(table_length, table.channel_pointer_read(0));

	// create output buffer
	types::cont_64 sample_rate = 44100.0;
	types::disc_32_u block_size = 1024;
	types::disc_32_u output_buffer_length = block_size * 155040;
	sample_buffer output_buffer(1, output_buffer_length);
	output_buffer.clear();

	// connect
	parameter::signal fm(0, -1.0f, 1.0f, static_cast<types::sample>(55.0 / sample_rate), static_cast<types::sample>(440.0 / sample_rate));
	//parameter::signal fm(0, -1.0f, 1.0f, 0.1f, 0.2f);
	carrier.parameter_plug("frequency", &fm);

	// prepare
	modulator.prepare(sample_rate, block_size);
	carrier.prepare(sample_rate, block_size);

	// perform
	modulator.frequency_set(static_cast<types::sample>(1.0 / sample_rate));
	types::disc_32_u i;
	for (i = 0; i < output_buffer_length / block_size; i++) {
		modulator.perform(output_buffer, block_size, 0, block_size * i);
		carrier.perform(output_buffer, block_size, 0, block_size * i);
	}

	// release
	modulator.release();
	carrier.release();

	// save
	helpers::io::wav_file_save("output.wav", sample_rate, 32, output_buffer);

    return 0;
}
