#ifndef EVALUATION_HPP_INCLUDED
#define EVALUATION_HPP_INCLUDED

#include <cmath>
#include <vector>

#include "beagle/GA.hpp"

#include "dependencies/kiss_fft130/kiss_fftr.h"

#include "cdsp.hpp"

using namespace cdsp;

extern void fft_buffer_size_calculate(types::index samples_num, types::index fft_n, types::index fft_overlap, types::index& fft_bins_per_frame, types::index& fft_num_frames, types::index& fft_output_buffer_length);
enum window_type {
	rect,
	hann
};
extern void fft_window(window_type type, sample_buffer& buffer);
extern void fft_real(types::index input_b_length, const types::sample* input_b, types::index fft_n, types::index fft_hop_size, const types::sample* window_b, kiss_fft_scalar* fft_in_b, kiss_fft_cpx* fft_out_b, types::cont_64* magnitude_b, types::cont_64* phase_b);

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

  PMOneVoiceEvalOp(types::index target_length, const types::sample* target_b, abstraction::pm_voice* voice_1, window_type fft_window_type, types::index fft_n, types::index fft_hop_size) :
	  Beagle::EvaluationOp("PMOneVoiceEvalOp"),
	  target_length(target_length),
	  target_b(target_b),
	  voice_1(voice_1),
	  candidate_sb(2, target_length),
	  fft_n(fft_n),
	  fft_hop_size(fft_hop_size),
	  fft_window_sb(1, fft_n),
	  error_min(values::infinity_64)
  {
	  fft_in_b = reinterpret_cast<kiss_fft_scalar*>(malloc(sizeof(kiss_fft_scalar) * fft_n));
	  fft_window(fft_window_type, fft_window_sb);

	  fft_buffer_size_calculate(target_length, fft_n, fft_hop_size, fft_bins_per_frame, fft_num_frames, fft_output_buffer_length);
	  
	  target_fft_out_b = reinterpret_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * fft_output_buffer_length));
	  target_magnitude_b = reinterpret_cast<types::cont_64*>(malloc(sizeof(types::cont_64) * fft_output_buffer_length));
	  target_phase_b = reinterpret_cast<types::cont_64*>(malloc(sizeof(types::cont_64) * fft_output_buffer_length));

	  fft_real(target_length, target_b, fft_n, fft_hop_size, fft_window_sb.channel_pointer_read(0), fft_in_b, target_fft_out_b, target_magnitude_b, target_phase_b);

	  candidate_fft_out_b = reinterpret_cast<kiss_fft_cpx*>(malloc(sizeof(kiss_fft_cpx) * fft_output_buffer_length));
	  candidate_magnitude_b = reinterpret_cast<types::cont_64*>(malloc(sizeof(types::cont_64) * fft_output_buffer_length));
	  candidate_phase_b = reinterpret_cast<types::cont_64*>(malloc(sizeof(types::cont_64) * fft_output_buffer_length));

	  candidate_best_params = reinterpret_cast<double*>(malloc(sizeof(double) * 4));
  };

  ~PMOneVoiceEvalOp() {
	  free(fft_in_b);
	  free(target_fft_out_b);
	  free(target_magnitude_b);
	  free(target_phase_b);
	  free(candidate_fft_out_b);
	  free(candidate_magnitude_b);
	  free(candidate_phase_b);
	  free(candidate_best_params);
  };

  virtual Beagle::Fitness::Handle evaluate(Beagle::Individual& inIndividual,
                                           Beagle::Context& ioContext);

private:
	// target
	types::index target_length;
	const types::sample* target_b;

	// synthesizer
	abstraction::pm_voice* voice_1;
	sample_buffer candidate_sb;

	// fft params
	types::index fft_n;
	types::index fft_hop_size;
	types::index fft_bins_per_frame;
	types::index fft_num_frames;
	types::index fft_output_buffer_length;

	// shared fft buffers
	kiss_fft_scalar* fft_in_b;
	sample_buffer fft_window_sb;

	// target fft buffers
	kiss_fft_cpx* target_fft_out_b;
	types::cont_64* target_magnitude_b;
	types::cont_64* target_phase_b;

	// candidate fft buffers
	kiss_fft_cpx* candidate_fft_out_b;
	types::cont_64* candidate_magnitude_b;
	types::cont_64* candidate_phase_b;

	// error
	types::cont_64 error_min;
	double* candidate_best_params;
};

#endif // PMOneVoiceEvalOp_hpp