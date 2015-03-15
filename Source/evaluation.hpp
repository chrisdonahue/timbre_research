#ifndef EVALUATION_H_INCLUDED
#define EVALUATION_H_INCLUDED

#include <vector>

#include "beagle/GA.hpp"

#include "dependencies/kiss_fft130/kiss_fft.h"

#include "cdsp.hpp"

using namespace cdsp;

void fft_buffer_size_calculate(types::index samples_num, types::index fft_n, types::index fft_overlap, types::index& fft_num_bins, types::index& fft_num_frames, types::index& fft_output_buffer_length) {
	fft_num_frames = 0;
	types::index fft_hop_size = fft_n - fft_overlap;
	types::index samples_completed = 0;
	types::index samples_remaining = samples_num;
	while (samples_remaining > 0) {
		fft_num_frames++;
		i += fft_hop_size;
	}
};

class PMOneVoiceEvalOpState
{
public:
	cdsp::types::index target_length;
	const cdsp::types::sample* target_buffer;
	cdsp::types::index candidate_block_size;
	cdsp::sample_buffer* candidate_sample_buffer;
	cdsp::abstraction::pm_voice* voice_1;
};

/*!
 *  \class PMOneVoiceEvalOp PMOneVoiceEvalOp.hpp "PMOneVoiceEvalOp.hpp"
 *  \ingroup PMOneVoice
 */
class PMOneVoiceEvalOp : public Beagle::EvaluationOp {

public:

  //! PMOneVoiceEvalOp allocator type.
  typedef Beagle::AllocatorT<PMOneVoiceEvalOp,Beagle::EvaluationOp::Alloc>
          Alloc;
  //!< PMOneVoiceEvalOp handle type.
  typedef Beagle::PointerT<PMOneVoiceEvalOp,Beagle::EvaluationOp::Handle>
          Handle;
  //!< PMOneVoiceEvalOp bag type.
  typedef Beagle::ContainerT<PMOneVoiceEvalOp,Beagle::EvaluationOp::Bag>
          Bag;

  PMOneVoiceEvalOp(PMOneVoiceEvalOpState* _state) : Beagle::EvaluationOp("PMOneVoiceEvalOp"), state(_state) {};

  virtual Beagle::Fitness::Handle evaluate(Beagle::Individual& inIndividual,
                                           Beagle::Context& ioContext);

private:
	PMOneVoiceEvalOpState* state;
};

#endif // PMOneVoiceEvalOp_hpp