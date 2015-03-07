#include "synths.hpp"

fm_voice::fm_voice() :
	modulator(values::sample_zero, values::sample_zero),
	multiplier_index(values::sample_zero),
	carrier_phasor(values::sample_zero, values::sample_zero),
	adder(static_cast<types::channel>(2)),
	carrier(),
	multiplier_amplitude(values::sample_zero)
{};

void fm_voice::table_set(types::index _table_length, const types::sample* _table) {
	modulator.table_set(_table_length, _table);
	carrier.table_set(_table_length, _table);
};

void fm_voice::reset() {
	modulator.phase_reset();
	carrier_phasor.phase_reset();
};

void fm_voice::prepare(types::cont_64 sample_rate, types::index block_size) {
	modulator.prepare(sample_rate, block_size);
	multiplier_index.prepare(sample_rate, block_size);
	carrier_phasor.prepare(sample_rate, block_size);
	adder.prepare(sample_rate, block_size);
	carrier.prepare(sample_rate, block_size);
	multiplier_amplitude.prepare(sample_rate, block_size);
};

void fm_voice::perform(sample_buffer& buffer, types::index block_size_leq, types::channel offset_channel, types::index offset_sample) {
	modulator.perform(buffer, block_size_leq, offset_channel, offset_sample);
	multiplier_index.perform(buffer, block_size_leq, offset_channel, offset_sample);
	carrier_phasor.perform(buffer, block_size_leq, offset_channel + 1, offset_sample);
	adder.perform(buffer, block_size_leq, offset_channel, offset_sample);
	carrier.perform(buffer, block_size_leq, offset_channel, offset_sample);
	multiplier_amplitude.perform(buffer, block_size_leq, offset_channel, offset_sample);
};

void fm_voice::release() {
	modulator.release();
	multiplier_index.release();
	carrier_phasor.release();
	adder.release();
	carrier.release();
	multiplier_amplitude.release();
};

void fm_voice::i_set(types::sample i) {
	multiplier_index.operand_set(i);
};

void fm_voice::f_m_set(types::sample f_m) {
	modulator.frequency_set(f_m);
};

void fm_voice::f_c_set(types::sample f_c) {
	carrier_phasor.frequency_set(f_c);
};

void fm_voice::a_set(types::sample a) {
	multiplier_amplitude.operand_set(a);
};
