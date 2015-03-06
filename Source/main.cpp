#include "../JuceLibraryCode/JuceHeader.h"

#include <iostream>

#include "cmaes.h"
//#include "dependencies/kiss_fft130/kiss_fft.c"
#include "cdsp/cdsp.hpp"

using namespace juce;
using namespace libcmaes;
using namespace cdsp;

class test {
public:
	test() : y(5) {};

	double fitness_function(const double* x, const int N) {
		std::cout << y << std::endl;
		return 0.0;
	};
private:
	int y;
};

int main (int argc, char* argv[]) {
	argc;
	argv;

	// read target
    File file("./target.wav");
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(file);
    if (reader == 0) {
		std::cout << "Couldn't find target.wav" << std::endl;
		return -1;
	}
	AudioSampleBuffer buffer(reader->numChannels, reader->lengthInSamples);
	reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);

	// target data
	types::index target_length = static_cast<types::index>(reader->lengthInSamples);
	types::cont_64 target_sample_rate = static_cast<types::cont_64>(reader->sampleRate);
	const types::sample* target_buffer = reinterpret_cast<const types::sample*>(buffer.getReadPointer(0, 0));

	// candidate data
	sample_buffer candidate_buffer(2, target_length);

	// sine wave table
	types::index sine_table_length = 2048;
	sample_buffer sine_table(1, sine_table_length);
	helpers::generators::sine(sine_table_length, sine_table.channel_pointer_write(values::channel_zero));

	// define fitness function
	FitFunc fm_simple_amplitude_error = [sine_table_length, &sine_table, &candidate_buffer, target_sample_rate, target_length, &target_buffer](const double *x, const int N)
	{
		// retrieve parameters
		types::sample i = static_cast<types::sample>(x[0]);
		types::sample f_m = static_cast<types::sample>(x[1]);
		types::sample f_c = static_cast<types::sample>(x[2]);
		types::sample a = static_cast<types::sample>(x[3]);

		// create modulator
		primitives::tables::oscillator::interpolate_4 modulator(values::sample_zero, static_cast<types::sample>(f_m / target_sample_rate));
		modulator.table_set(sine_table_length, sine_table.channel_pointer_read(values::channel_zero));

		// create multiplier_index
		primitives::operators::multiply multiplier_index(i);

		// create phasor
		primitives::oscillators::phasor carrier_phasor(values::sample_zero, static_cast<types::sample>(f_c / target_sample_rate));

		// create adder
		primitives::operators::add adder(static_cast<types::channel>(2));

		// create carrier
		primitives::tables::phasor::interpolate_4 carrier;
		carrier.table_set(sine_table_length, sine_table.channel_pointer_read(values::channel_zero));

		// create multiplier_amplitude
		primitives::operators::multiply multiplier_amplitude(a);

		// prepare
		modulator.prepare(target_sample_rate, target_length);
		multiplier_index.prepare(target_sample_rate, target_length);
		carrier_phasor.prepare(target_sample_rate, target_length);
		adder.prepare(target_sample_rate, target_length);
		carrier.prepare(target_sample_rate, target_length);
		multiplier_amplitude.prepare(target_sample_rate, target_length);

		// clear output buffer
		candidate_buffer.clear();

		// perform
		modulator.perform(candidate_buffer, target_length, 0, 0);
		multiplier_index.perform(candidate_buffer, target_length, 0, 0);
		carrier_phasor.perform(candidate_buffer, target_length, 1, 0);
		adder.perform(candidate_buffer, target_length, 0, 0);
		carrier.perform(candidate_buffer, target_length, 0, 0);
		multiplier_amplitude.perform(candidate_buffer, target_length, 0, 0);

		// release
		modulator.release();
		multiplier_index.release();
		carrier_phasor.release();
		adder.release();
		carrier.release();
		multiplier_amplitude.release();

		// resize
		//buffer.resize(1, buffer.channel_buffer_length_get());

		// save
		//helpers::io::wav_file_save("fm_simple.wav", target_sample_rate, 32, buffer);

		// return fitness function result
		types::sample error = 0.0;
		types::index samples_remaining = target_length;
		const types::sample* target = target_buffer;
		const types::sample* candidate = candidate_buffer.channel_pointer_read(values::channel_zero);
		while (samples_remaining--) {
			error += fabs(*(target++) - *(candidate++));
		}
		return static_cast<double>(error);
	};

	// define cmaes parameters
	// https://www.lri.fr/~hansen/cmaes_inmatlab.html#practical
	// https://github.com/beniz/libcmaes/wiki/Practical-hints
	int dim = 4;
	double sigma = 0.1;
	int lambda = -1;
	uint64_t seed = 0;

	// define solution bounds
	double lbounds[] = {0.0, 0.0, 0.0, 0.0};
	double ubounds[] = {22050.0, 10.0, 44100.0, 1.0};
	GenoPheno<pwqBoundStrategy> gp(lbounds, ubounds, dim);

	// define solution initial values
	std::vector<double> x0 = {100.0, 1.0, 440.0, 1.0};

	// test
	test a;
	FitFunc afun = [&a](const double *x, const int N) {
		return a.fitness_function(x, N);
	};

	// run cmaes
	CMAParameters<GenoPheno<pwqBoundStrategy>> cmaparams(x0, sigma, lambda, seed, gp);
	cmaparams.set_algo(aCMAES);
	CMASolutions cmasols = cmaes<GenoPheno<pwqBoundStrategy>>(afun, cmaparams);

	// output best
	std::cout << "best solution: " << cmasols << std::endl;
	std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";

	// return
	return cmasols.run_status();
};
