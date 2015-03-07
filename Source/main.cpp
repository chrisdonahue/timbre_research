#include "../JuceLibraryCode/JuceHeader.h"

#include <iostream>

#include "cmaes.h"
//#include "dependencies/kiss_fft130/kiss_fft.c"
#include "cdsp/cdsp.hpp"

#include "synths.hpp"

using namespace juce;
using namespace libcmaes;

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

	// create voice
	fm_voice voice_1;
	voice_1.table_set(sine_table_length, sine_table.channel_pointer_read(values::channel_zero));

	// test voice
	voice_1.i_set(static_cast<types::sample>(1.0f));
	voice_1.f_m_set(static_cast<types::sample>(100.0f));
	voice_1.f_c_set(static_cast<types::sample>(440.0f));
	voice_1.a_set(static_cast<types::sample>(0.67f));
	voice_1.prepare(target_sample_rate, target_length);
	voice_1.perform(candidate_buffer, target_length, 0, 0);
	candidate_buffer.resize(1, target_length);
	helpers::io::wav_file_save("voice_1_test.wav", target_sample_rate, 32, candidate_buffer);
	candidate_buffer.resize(2, target_length);

	// define fitness function
	FitFunc fm_simple_error_amp = [&voice_1, &candidate_buffer, &target_buffer](const double *x, const int N)
	{
		// set parameters
		voice_1.i_set(static_cast<types::sample>(x[0]));
		voice_1.f_m_set(static_cast<types::sample>(x[1]));
		voice_1.f_c_set(static_cast<types::sample>(x[2]));
		voice_1.a_set(static_cast<types::sample>(x[3]));

		types::index target_length = candidate_buffer.channel_buffer_length_get();

		// perform
		voice_1.perform(candidate_buffer, target_length, 0, 0);

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

	// configure libcmaes
	CMAParameters<GenoPheno<pwqBoundStrategy>> cmaparams(x0, sigma, lambda, seed, gp);
	cmaparams.set_algo(aCMAES);

	// run cmaes
	CMASolutions cmasols = cmaes<GenoPheno<pwqBoundStrategy>>(fm_simple_error_amp, cmaparams);

	// release voice
	voice_1.release();

	// output best
	std::cout << "best solution: " << cmasols << std::endl;
	std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";

	// return
	return cmasols.run_status();
};
