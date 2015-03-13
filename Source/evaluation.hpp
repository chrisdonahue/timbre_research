#ifndef EVALUATION_H_INCLUDED
#define EVALUATION_H_INCLUDED

#include "beagle/GA.hpp"
#include <vector>

#include "cdsp.hpp"

class PMOneVoiceParams : public Beagle::Object
{
public:
	//! PMOneVoiceParams allocator type.
	typedef Beagle::AllocatorT<PMOneVoiceParams,Beagle::Object::Alloc>
	Alloc;
	//!< PMOneVoiceParams handle type.
	typedef Beagle::PointerT<PMOneVoiceParams,Beagle::Object::Handle>
	Handle;
	//!< PMOneVoiceParams bag type.
	typedef Beagle::ContainerT<PMOneVoiceParams,Beagle::Object::Bag>
	Bag;

	explicit PMOneVoiceParams();

	cdsp::types::cont_64 target_sample_rate;
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

  explicit PMOneVoiceEvalOp();

  virtual Beagle::Fitness::Handle evaluate(Beagle::Individual& inIndividual,
                                           Beagle::Context& ioContext);

private:
};

#endif // PMOneVoiceEvalOp_hpp