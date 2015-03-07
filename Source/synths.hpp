#ifndef SYNTHS_H_INCLUDED
#define SYNTHS_H_INCLUDED

#include "cdsp/cdsp.hpp"

using namespace cdsp;

class fm_voice {
public:
	fm_voice();

	void table_set(types::index _table_length, const types::sample* _table);

	void reset();

	void prepare(types::cont_64 target_sample_rate, types::index block_size);
	void perform(sample_buffer& buffer, types::index block_size_leq, types::channel offset_channel = 0, types::index offset_sample = 0);
	void release();

	void i_set(types::sample i);
	void f_m_set(types::sample f_m);
	void f_c_set(types::sample f_c);
	void a_set(types::sample a);

private:
	primitives::tables::oscillator::interpolate_4 	modulator;
	primitives::operators::multiply 				multiplier_index;
	primitives::oscillators::phasor					carrier_phasor;
	primitives::operators::add						adder;
	primitives::tables::phasor::interpolate_4		carrier;
	primitives::operators::multiply					multiplier_amplitude;
};


#endif
