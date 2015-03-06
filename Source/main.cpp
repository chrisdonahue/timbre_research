#include "../JuceLibraryCode/JuceHeader.h"

//#include "cmaes.h"
#include <iostream>

#include "cdsp/cdsp.hpp"

//using namespace libcmaes;

using namespace cdsp;

/*
FitFunc fsphere = [](const double *x, const int N)
{
	double val = 0.0;
	for (int i=0;i<N;i++)
		val += x[i]*x[i];
	return val;
};
*/

void two_sine_waves() {
	// create wavetable
	types::disc_32_u table_length = 1024;
	sample_buffer table(1, table_length);
	helpers::generators::sine(table_length, table.channel_pointer_write(0));

	// create output buffer
	types::cont_64 sample_rate = 44100.0;
	types::disc_32_u block_size = 1024;
	types::disc_32_u output_buffer_length = block_size * 128;
	sample_buffer output_buffer(2, output_buffer_length);
	output_buffer.clear();

	// create oscillator_1
	primitives::tables::oscillator::interpolate_4 oscillator_1(values::sample_zero, static_cast<types::sample>(440.0 / sample_rate));
	oscillator_1.table_set(table_length, table.channel_pointer_read(0));

	// create multiplier_1
	primitives::operators::multiply multiplier_1(static_cast<types::sample>(0.5f));

	// create oscillator_2
	primitives::tables::oscillator::interpolate_4 oscillator_2(values::sample_zero, static_cast<types::sample>(220.0 / sample_rate));
	oscillator_2.table_set(table_length, table.channel_pointer_read(0));

	// create multiplier_2
	primitives::operators::multiply multiplier_2(static_cast<types::sample>(0.5f));

	// create adder
	primitives::operators::add adder(static_cast<types::channel>(2));

	// create ramp
	primitives::envelopes::interpolate_linear envelope;

	// create multiplier_3
	primitives::operators::multiply multiplier_3(static_cast<types::channel>(2));

	// prepare
	oscillator_1.prepare(sample_rate, block_size);
	multiplier_1.prepare(sample_rate, block_size);
	oscillator_2.prepare(sample_rate, block_size);
	multiplier_2.prepare(sample_rate, block_size);
	adder.prepare(sample_rate, block_size);
	envelope.prepare(sample_rate, block_size);
	multiplier_3.prepare(sample_rate, block_size);

	// add envelope points
	envelope.point_add(1.0, 1.0);
	envelope.point_add(0.2, 0.5);
	envelope.point_add(0.8, 0.0);

	// perform
	types::disc_32_u i;
	for (i = 0; i < output_buffer_length / block_size; i++) {
		oscillator_1.perform(output_buffer, block_size, 0, block_size * i);
		multiplier_1.perform(output_buffer, block_size, 0, block_size * i);
		oscillator_2.perform(output_buffer, block_size, 1, block_size * i);
		multiplier_2.perform(output_buffer, block_size, 1, block_size * i);
		adder.perform(output_buffer, block_size, 0, block_size * i);
		envelope.perform(output_buffer, block_size, 1, block_size * i);
		multiplier_3.perform(output_buffer, block_size, 0, block_size * i);
	}

	// release
	oscillator_1.release();
	multiplier_1.release();
	oscillator_2.release();
	multiplier_2.release();
	adder.release();
	envelope.release();
	multiplier_3.release();

	// resize
	output_buffer.resize(1, output_buffer_length);

	// save
	helpers::io::wav_file_save("two_sine_waves.wav", sample_rate, 32, output_buffer);
};

void phasor() {
	// create output buffer
	types::cont_64 sample_rate = 44100.0;
	types::disc_32_u block_size = 1024;
	types::disc_32_u output_buffer_length = block_size * 32;
	sample_buffer output_buffer(1, output_buffer_length);
	output_buffer.clear();

	// create phasor
	primitives::oscillators::phasor phasor(values::sample_zero, static_cast<types::sample>(55.0 / sample_rate));

	// prepare
	phasor.prepare(sample_rate, block_size);

	// perform
	types::disc_32_u i;
	for (i = 0; i < output_buffer_length / block_size; i++) {
		phasor.perform(output_buffer, block_size, 0, block_size * i);
	}

	// release
	phasor.release();

	// save
	helpers::io::wav_file_save("phasor.wav", sample_rate, 32, output_buffer);
};

void fm_simple_render(std::unordered_map<types::string, types::sample>& parameters, sample_buffer& buffer) {
	// create output buffer
	types::cont_64 sample_rate = 44100.0;
	types::index block_size = 1024;

	// retrieve parameters
	types::sample i = parameters.find("i")->second;
	types::sample f_m = parameters.find("f_m")->second;
	types::sample f_c = parameters.find("f_c")->second;
	types::sample a = parameters.find("a")->second;

	// create sine wave table
	types::index table_length = 2048;
	sample_buffer table(1, table_length);
	helpers::generators::sine(table_length, table.channel_pointer_write(values::channel_zero));

	// create modulator
	primitives::tables::oscillator::interpolate_4 modulator(values::sample_zero, static_cast<types::sample>(f_m / sample_rate));
	modulator.table_set(table_length, table.channel_pointer_read(values::channel_zero));

	// create multiplier_index
	primitives::operators::multiply multiplier_index(i);

	// create phasor
	primitives::oscillators::phasor carrier_phasor(values::sample_zero, static_cast<types::sample>(f_c / sample_rate));

	// create adder
	primitives::operators::add adder(static_cast<types::channel>(2));

	// create carrier
	primitives::tables::phasor::interpolate_4 carrier;
	carrier.table_set(table_length, table.channel_pointer_read(values::channel_zero));

	// create multiplier_amplitude
	primitives::operators::multiply multiplier_amplitude(a);

	// prepare
	modulator.prepare(sample_rate, block_size);
	multiplier_index.prepare(sample_rate, block_size);
	carrier_phasor.prepare(sample_rate, block_size);
	adder.prepare(sample_rate, block_size);
	carrier.prepare(sample_rate, block_size);
	multiplier_amplitude.prepare(sample_rate, block_size);

	// clear output buffer
	buffer.clear();

	// perform
	types::index samples_remaining = buffer.channel_buffer_length_get();
	types::index samples_completed = 0;
	while (samples_remaining > 0) {
		types::index block_size_current = block_size;
		if (samples_remaining < block_size) {
			block_size_current = samples_remaining;
		}

		modulator.perform(buffer, block_size_current, 0, samples_completed);
		multiplier_index.perform(buffer, block_size_current, 0, samples_completed);
		carrier_phasor.perform(buffer, block_size_current, 1, samples_completed);
		adder.perform(buffer, block_size_current, 0, samples_completed);
		carrier.perform(buffer, block_size_current, 0, samples_completed);
		multiplier_amplitude.perform(buffer, block_size_current, 0, samples_completed);

		samples_remaining -= block_size_current;
		samples_completed += block_size_current;
	}

	// release
	modulator.release();
	multiplier_index.release();
	carrier_phasor.release();
	adder.release();
	carrier.release();
	multiplier_amplitude.release();

	// resize
	buffer.resize(1, buffer.channel_buffer_length_get());

	// save
	helpers::io::wav_file_save("fm_simple.wav", sample_rate, 32, buffer);
};

int main (int argc, char* argv[]) {
	argc;
	argv;

	//two_sine_waves();

	//phasor();
	

	// create parameters
	std::unordered_map<types::string, types::sample> parameters;
	parameters.insert(std::make_pair("i", 1.0f));
	parameters.insert(std::make_pair("f_c", 440.0f));
	parameters.insert(std::make_pair("f_m", 100.0f));
	parameters.insert(std::make_pair("a", 0.5f));

	// create buffer
	sample_buffer buffer(2, 1024 * 128);
	fm_simple_render(parameters, buffer);

	// test cmaes
	/*
	int dim = 10; // problem dimensions.
	std::vector<double> x0(dim,10.0);
	double sigma = 0.1;
	//int lambda = 100; // offsprings at each generation.
	CMAParameters<> cmaparams(dim,&x0.front(),sigma);
	//cmaparams.set_algo(BIPOP_CMAES);
	CMASolutions cmasols = cmaes<>(fsphere,cmaparams);
	std::cout << "best solution: " << cmasols << std::endl;
	std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";
	return cmasols.run_status();
	*/

    //return 0;
};
