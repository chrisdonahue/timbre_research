#include "../JuceLibraryCode/JuceHeader.h"

#include <iostream>

#include "cdsp.hpp"
#include "beagle/GA.hpp"

#include "evaluation.hpp"

using namespace cdsp;
using namespace Beagle;

int main (int argc, char** argv) {
	// read target
    File file("C:\\Code\\timbre_research\\Builds\\VisualStudio2012\\Debug\\target.wav");
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
	types::index candidate_block_size = 1024;

	// sine wave table
	types::index sine_table_length = 2048;
	sample_buffer sine_table(1, sine_table_length);
	helpers::generators::sine(sine_table_length, sine_table.channel_pointer_write(values::channel_zero));

	// create voice
	abstraction::pm_voice voice_1;
	voice_1.table_set(sine_table_length, sine_table.channel_pointer_read(values::channel_zero));
	voice_1.prepare(target_sample_rate, candidate_block_size);

	// create state
	PMOneVoiceEvalOpState* state = new PMOneVoiceEvalOpState();
	state->target_length = target_length;
	state->target_buffer = target_buffer;
	state->candidate_block_size = candidate_block_size;
	state->candidate_sample_buffer = &candidate_buffer;
	state->voice_1 = &voice_1;

	try {
		// 1. Build the system.
		System::Handle lSystem = new System;
		// 2. Build evaluation operator.
		PMOneVoiceEvalOp::Handle lEvalOp = new PMOneVoiceEvalOp(state);
		//PMOneVoiceEvalOp::Handle lEvalOp = new PMOneVoiceEvalOp;
		// 3. Instanciate the evolver and the vivarium for float vectors GA population.
		GA::FloatVector::Alloc::Handle lFVAlloc = new GA::FloatVector::Alloc;
		Vivarium::Handle lVivarium = new Vivarium(lFVAlloc);
		// 4. Set representation, float vectors of 5 values.
		const unsigned int lVectorSize = 4;  
		// 5. Initialize the evolver and evolve the vivarium.
		GA::EvolverFloatVector::Handle lEvolver = new GA::EvolverFloatVector(lEvalOp, lVectorSize);
		lEvolver->initialize(lSystem, "C:\\Code\\timbre_research\\Builds\\VisualStudio2012\\Debug\\cmaes_no_milestone.conf");
		lEvolver->evolve(lVivarium);
	}
	catch(Exception& inException) {
		inException.terminate(std::cerr);
	}
	catch(std::exception& inException) {
		std::cerr << "Standard exception catched:" << std::endl << std::flush;
		std::cerr << inException.what() << std::endl << std::flush;
		return 1;
	}

	// delete state
	delete state;

	// release pm voice
	voice_1.release();

	return 0;
};
