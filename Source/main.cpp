#include "../JuceLibraryCode/JuceHeader.h"

#include "cdsp/cdsp.hpp"

int main (int argc, char* argv[]) {
	argc;
	argv;

	using namespace cdsp;

	primitive::oscillator::table_interpolate_4 oscillator;
	types::disc_32_u table_length = 16;
	types::sample* table = static_cast<types::sample*>(malloc(table_length * sizeof(types::sample)));
	helpers::sine_sum(std::map<types::cont_32, types::cont_32>(), table_length, table);

    return 0;
}
