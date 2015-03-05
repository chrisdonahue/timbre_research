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
	primitives::oscillators::table_interpolate_4 oscillator_1(values::sample_zero, static_cast<types::sample>(440.0 / sample_rate));
	oscillator_1.table_set(table_length, table.channel_pointer_read(0));

	// create multiplier_1
	primitives::operators::multiply multiplier_1(static_cast<types::sample>(0.5f));

	// create oscillator_2
	primitives::oscillators::table_interpolate_4 oscillator_2(values::sample_zero, static_cast<types::sample>(220.0 / sample_rate));
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

int main (int argc, char* argv[]) {
	argc;
	argv;

	two_sine_waves();

	//phasor();

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
