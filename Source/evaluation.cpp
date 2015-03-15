#include "evaluation.hpp"

#include <cmath>

using namespace Beagle;

void fft_buffer_size_calculate(types::index samples_num, types::index fft_n, types::index fft_overlap, types::index& fft_bins_per_frame, types::index& fft_num_frames, types::index& fft_output_buffer_length) {
	fft_num_frames = 0;
	types::index fft_hop_size = fft_n - fft_overlap;
	types::index samples_completed = 0;
	types::index samples_remaining = samples_num;
	types::index samples_current;
	while (samples_remaining > 0) {
		samples_current = fft_n;
		if (samples_remaining >= fft_n) {
			samples_current = samples_remaining;
		}
		fft_num_frames++;
		samples_completed += fft_hop_size;
		samples_remaining -= fft_hop_size;
	}
	fft_bins_per_frame = ((fft_n / 2) + 1);
	fft_output_buffer_length = fft_num_frames * fft_bins_per_frame;
};

void fft_window(window_type type, sample_buffer& buffer) {
	types::index samples_remaining = buffer.channel_buffer_length_get();
	types::sample* samples = buffer.channel_pointer_write(0);
	switch (type) {
	case window_type::rect:
		while (samples_remaining--) {
			*(samples++) = values::sample_one;
		}
		break;
	case window_type::hann:
		types::cont_64 cos_inner = values::zero_64;
		types::cont_64 cos_inner_increment = (values::two_pi_64) / static_cast<types::cont_64>(samples_remaining - 1);
		while (samples_remaining--) {
			*(samples++) = static_cast<types::cont_64>(0.5) * (values::one_64 - cos(cos_inner));
			cos_inner += cos_inner_increment;
		}
		break;
	}
};

void fft_real(types::index input_b_length, const types::sample* input_b, types::index fft_n, types::index fft_hop_size, const types::sample* window_b, kiss_fft_scalar* fft_in_b, kiss_fft_cpx* fft_out_b, types::cont_64* magnitude_b, types::cont_64* phase_b) {
	kiss_fftr_cfg cfg = kiss_fftr_alloc(fft_n, 0, NULL, NULL);

	types::index fft_bins_per_frame = (fft_n / 2 + 1);
	types::index samples_completed = 0;
	types::index samples_remaining = input_b_length;
	types::index samples_current;
	types::index fft_bins_computed = 0;
	while (samples_remaining > 0) {
		// calculate number of samples for input buffer
		samples_current = fft_n;
		if (samples_remaining <= fft_n) {
			samples_current = samples_remaining;
		}
		
		// fill input buffer
		types::index i;
		for (i = 0; i < samples_current; i++) {
			fft_in_b[i] = static_cast<kiss_fft_scalar>(input_b[samples_completed + i]);
		}
		samples_completed += fft_hop_size;
		samples_remaining -= fft_hop_size;

		// zero pad
		for (; i < fft_n; i++) {
			fft_in_b[i] = static_cast<kiss_fft_scalar>(values::sample_zero);
		}

		// apply window
		for (i = 0; i < fft_n; i++) {
			fft_in_b[i] *= static_cast<kiss_fft_scalar>(window_b[i]);
		}

		// perform fft
		kiss_fftr(cfg, fft_in_b, fft_out_b + fft_bins_computed);

		// calculate magnitude and phase
		for (types::index bin = fft_bins_computed; bin < fft_bins_computed + fft_bins_per_frame; bin++) {
            magnitude_b[bin] = sqrt(fft_out_b[bin].r * fft_out_b[bin].r + fft_out_b[bin].i * fft_out_b[bin].i);
            if (fft_out_b[bin].r == 0 && fft_out_b[bin].i == 0) {
                phase_b[bin] = values::zero_64;
            }
            else {
                phase_b[bin] = atan(fft_out_b[bin].i / fft_out_b[bin].r);
            }
		}
		fft_bins_computed += fft_bins_per_frame;
	}

	free(cfg);
};

/*!
 *  \brief Evaluate the fitness of the given individual.
 *  \param inIndividual Current individual to evaluate.
 *  \param ioContext Evolutionary context.
 *  \return Handle to the fitness value of the individual.
 */
Fitness::Handle PMOneVoiceEvalOp::evaluate(Individual& inIndividual, Context& ioContext)
{
	Beagle_AssertM(inIndividual.size() == 1);
	GA::FloatVector::Handle lFloatVector = castHandleT<GA::FloatVector>(inIndividual[0]);
	Beagle_AssertM(lFloatVector->size() == 4);
	for (unsigned int i = 0; i < 4; i++) {
		double lXi = (*lFloatVector)[i];
		if(lXi > 1.0) {
			lXi = 1.0;
		}
		if(lXi < -1.0) {
			lXi = -1.0;
		}
		switch (i) {
		case 0:
			voice_1->f_m_set(static_cast<types::sample>(lXi));
			break;
		case 1:
			voice_1->i_set(static_cast<types::sample>(lXi * 10.0));
			break;
		case 2:
			voice_1->f_c_set(static_cast<types::sample>(lXi));
			break;
		case 3:
			voice_1->a_set(static_cast<types::sample>(lXi));
			break;
		default:
			continue;
		}
	}

	// perform
	voice_1->reset();
	voice_1->perform(candidate_sb, target_length, 0, 0);

	// fft
	fft_real(target_length, candidate_sb.channel_pointer_read(0), fft_n, fft_hop_size, fft_window_sb.channel_pointer_read(0), fft_in_b, candidate_fft_out_b, candidate_magnitude_b, candidate_phase_b);

	// return fitness function result
	types::cont_64 error = 0.0;
	types::index bins_remaining = fft_num_frames * fft_bins_per_frame;
	for (types::index bin = 0; bin < fft_output_buffer_length; bin++) {
		error += fabs(target_magnitude_b[bin] - candidate_magnitude_b[bin]);
	}
	if (error < error_min) {
		helpers::io::wav_file_save("best.wav", 44100.0, 32, candidate_sb, 0);
		error_min = error;
	}
	return new FitnessSimpleMin(static_cast<double>(error));
}