#include "evaluation.hpp"

#include <cmath>

using namespace Beagle;

PMOneVoiceParams::PMOneVoiceParams() 
{ }

/*!
 *  \brief Construct the individual evaluation operator for maximizing the function.
 */
PMOneVoiceEvalOp::PMOneVoiceEvalOp() :
  EvaluationOp("PMOneVoiceEvalOp")
{
}

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
  Beagle_AssertM(lFloatVector->size() == 5);
  double lU   = 10.0;
  double lSum = 0.0;
  for(unsigned int i=0; i<5; ++i) {
    double lXi = (*lFloatVector)[i];
    if(lXi > 200.0)  lXi = 200.0;
    if(lXi < -200.0) lXi = -200.0;
    lSum += (lXi*lXi) + (lU*lU);
    lU += lXi;
  }
  lSum += (lU*lU);
  double lF = 161.8 / lSum;
  return new FitnessSimple(lF);

  /*
  		// set parameters
		voice_1.f_m_set(static_cast<types::sample>(x[0]/target_sample_rate));
		voice_1.i_set(static_cast<types::sample>(x[1]));
		voice_1.f_c_set(static_cast<types::sample>(x[2]/target_sample_rate));
		voice_1.a_set(static_cast<types::sample>(x[3]));

		std::cout << "{" << x[0] << ", "
						<< x[1] << ", "
						<< x[2] << ", "
						<< x[3] << "}" << std::endl;

		types::index target_length = candidate_buffer.channel_buffer_length_get();

		// perform
		voice_1.reset();
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
  */
}
