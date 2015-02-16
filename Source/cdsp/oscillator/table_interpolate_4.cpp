#include "table_oscillator.hpp"

void cdsp::oscillator::table_interpolate_4::prepare(double sample_rate, int block_size) {
};

void cdsp::oscillator::table_interpolate_4::release() {
};

void cdsp::oscillator::table_interpolate_4::perform(int block_size, float** channels_input, float** channels_output);
