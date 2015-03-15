#include "evaluation.hpp"

#include <cmath>

using namespace Beagle;

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
			state->voice_1->f_m_set(static_cast<types::sample>(lXi));
		case 1:
			state->voice_1->i_set(static_cast<types::sample>(lXi * 10.0));
		case 2:
			state->voice_1->f_c_set(static_cast<types::sample>(lXi));
		case 3:
			state->voice_1->a_set(static_cast<types::sample>(lXi));
		default:
			continue;
		}
	}

	// perform
	state->voice_1->reset();
	state->voice_1->perform(*(state->candidate_sample_buffer), state->target_length, 0, 0);

	// return fitness function result
	types::sample error = 0.0;
	types::index samples_remaining = state->target_length;
	const types::sample* target = state->target_buffer;
	const types::sample* candidate = state->candidate_sample_buffer->channel_pointer_read(values::channel_zero);
	while (samples_remaining--) {
		error += fabs(*(target++) - *(candidate++));
	}
	return new FitnessSimpleMin(static_cast<double>(error));
}