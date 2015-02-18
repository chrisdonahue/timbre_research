#include "base.hpp"

cdsp::primitive::base::base() {
}

cdsp::primitive::base::~base() {
}

void cdsp::primitive::base::prepare(types::cont_64 sample_rate, types::disc_32_u block_size) {
	sample_rate;
	block_size;
};

void cdsp::primitive::base::release() {
};