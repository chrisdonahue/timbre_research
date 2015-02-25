#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <unordered_map>
#include <vector>

#include "base.hpp"
#include "defines.hpp"
#include "exceptions.hpp"
#include "types.hpp"
#include "values.hpp"

#include "primitive/primitive_base.hpp"

namespace cdsp {
	class graph : public dsp {
	public:
		graph();
		~graph();

		// prepare
		void prepare(types::cont_64 sample_rate, types::disc_32_u block_size);
		void release();
		void perform();

		// add and remove nodes
		types::disc_32_u node_add(primitive::base* _primitive);
		void node_remove(types::disc_32_u id);

		// plug to output
		void node_output_plug(types::disc_32_u input);
		void node_output_unplug(types::disc_32_u input);

		// plug and unplug two nodes
		void node_node_plug(types::disc_32_u input, types::disc_32_u output);
		void node_node_unplug(types::disc_32_u input, types::disc_32_u output);

		// plug and unplug audio-rate parameters
		void node_parameter_plug(types::disc_32_u input, types::disc_32_u output, types::string parameter_specifier);
		void node_parameter_unplug(types::disc_32_u input, types::disc_32_u output, types::string parameter_specifier);

		// graph sanity tests
		void test_fully_connected();
		void test_acyclic();

	private:
		class node {
		public:
			node(primitive::base* _primitive);
			~node();

		private:
			types::disc_32_u id;
			std::vector<node*> incident;
		};

		class exception : public exceptions::base {
		public:
			exception(const std::string& msg) : exceptions::base(msg) {};
		};

		std::unordered_map<types::disc_32_u, node*> nodes;
	};
}

#endif