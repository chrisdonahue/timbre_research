#include "primitive.hpp"

cdsp::primitive::primitive() {
	parameters_add();
}

cdsp::primitive::~primitive() {
}

void cdsp::primitive::prepare(types::cont_64 sample_rate, types::disc_32_u block_size) {
	sample_rate;
	block_size;
};

void cdsp::primitive::release() {
};

void cdsp::primitive::parameters_add() {
};
