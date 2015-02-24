#include "../JuceLibraryCode/JuceHeader.h"

#include <vector>

#include "cdsp/cdsp.hpp"

int main (int argc, char* argv[]) {
	argc;
	argv;

	using namespace cdsp;
	
	/*
	// create modulator
	primitive::oscillator::table_interpolate_4 modulator;
	types::disc_32_u table_length = 1024;
	sample_buffer table(1, table_length);
	helpers::sine_sum(std::unordered_map<types::cont_32, types::cont_32>(), table_length, table.channel_pointer_write(0));
	modulator.table_set(table_length, table.channel_pointer_read(0));

	// create carrier
	primitive::oscillator::table_interpolate_4 carrier;
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
	*/

	// create control signal
	std::vector<types::disc_32_u> harmonics_max = { 1, 1024, 1024 * 2, 1024 * 3, 1024 * 4};
	types::disc_32_u table_length = 2048;

	// create table
	types::disc_32_u table_length_total = harmonics_max.size() * table_length;
	sample_buffer table(1, table_length_total + 3);
	table.clear();
	types::sample* table_buffer = table.channel_pointer_write(0, 0);
	table_buffer[0] = values::sample_silence;
	table_buffer[table_length_total - 1] = values::sample_silence;
	table_buffer[table_length_total - 2] = values::sample_silence;

	std::set<std::tuple<types::cont_64, types::cont_64, types::cont_64> > harmonics;
	types::disc_32_u i = 0;
	for (auto it : harmonics_max) {
		types::disc_32_u harmonic_max = it;
		harmonics.clear();
		for (types::disc_32_u h = 1; h <= harmonic_max; h++) {
			types::cont_64 harmonic_freq = static_cast<types::cont_64>(h);
			types::cont_64 harmonic_amp = 1.0 / harmonic_freq;
			harmonics.insert(std::make_tuple(harmonic_freq, harmonic_amp, 0.5));
		}
		helpers::sine_sum(harmonics, table_length, table.channel_pointer_write(0, 1 + (i * table_length)));
		i += 1;
	}

	// save
	types::cont_64 sample_rate = 44100.0;
	helpers::io::wav_file_save("envelope.wav", sample_rate, 32, table);

    return 0;
}
