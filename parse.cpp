#include <fstream>
#include <sstream>
#include <algorithm>
#include "parse.h"

namespace snu {

	// parse .snu file
	DSGraph *parse_snu_DSGraph(std::string file_path) {
		std::ifstream infile(file_path);
		std::string line;
		DSGraph *graph = new DSGraph();
		Graph::Eid eid = 0;

		while(getline(infile, line)) {
			std::istringstream iss(line);

			std::string sign;
			iss >> sign;
			if(sign == "t") {}
			else if(sign == "v") {
				Graph::Vid id;
				Graph::Vlabel label;
				std::vector <Graph::Vlabel> label_vector;

				iss >> id;
				while(iss >> label) label_vector.push_back(label);
				if(graph->add_vertex(id, &label_vector)) { // error
					delete graph;
					return NULL;
				}
			}
			else if(sign == "e") {
				Graph::Vid from, to;
				Graph::Elabel label;
				std::vector<Graph::Elabel> label_vector;

				iss >> from >> to;
				while(iss >> label) label_vector.push_back(label);
				if(graph->add_edge(eid++, &label_vector, from, to, 1)) { // error
					delete graph;
					return NULL;
				}
			}
			else { // error
				delete graph;
				return NULL;
			}
		}

		return graph;
	}

	// parse .net file
	DSGraph *parse_net_DSGraph(std::string file_path) {
		DSGraph *graph = new DSGraph();
		std::ifstream infile(file_path);
		std::string line;
		int check_vertex = 0;
		int check_edge = 0;

		while(getline(infile, line)) {
			std::istringstream iss(line);

			if(line.find("*Vertices") != std::string::npos || line.find("*vertices") != std::string::npos) {
				check_vertex = 1;
				check_edge = 0;
				continue;
			}
			else if(line.find("*arcs") != std::string::npos || line.find("*Arcs") != std::string::npos) {
				check_edge = 1;
				check_vertex = 0;
				continue;
			}

			if(check_vertex==1) {
				Graph::Vid id;
				std::vector <Graph::Vlabel> label_vector;
				Graph::Vlabel label;
				iss >> id;

				while(iss >> label) {
					label.erase(std::remove(label.begin(), label.end(), '\"'), label.end());
					label_vector.push_back(label);
				}
				graph->add_vertex(id, &label_vector);
			}

			if(check_edge==1) {
				Graph::Eid id;
				Graph::Vid from;
				Graph::Vid to;
				std::vector <Graph::Elabel> label_vector;
				Graph::Elabel label;

				iss >> id;
				iss >> from;
				iss >> to;
				while(iss >> label){
					if(label == "l") continue;
					label.erase(std::remove(label.begin(), label.end(), '\"'), label.end());
					label_vector.push_back(label);
				}
				graph->add_edge(id, &label_vector, from, to, 1);
			}
		}
		return graph;
	}

	// parse .snap file
	DSGraph *parse_snap_DSGraph(std::string file_path) {
		std::ifstream infile(file_path);
		std::string line;
		DSGraph *graph = new DSGraph();
		std::unordered_set <int> set;
		Graph::Eid eid = 0;

		while(getline(infile, line)) {
			std::istringstream iss(line);

			if(line.find("#") != std::string::npos)
				continue;

			Graph::Vid from, to;
			iss >> from >> to;

			if(!set.count(from)) {
				set.insert(from);
				graph->add_vertex(from, 0, NULL);
			}
			if(!set.count(to)) {
				set.insert(to);
				graph->add_vertex(to, 0, NULL);
			}

			// add edge
			graph->add_edge(eid++, 0, NULL, from, to, 1);
		}

		return graph;
	}

	// parsing DSGraph version follows
	DSGraph *parse_DSGraph(std::string file_path) {
		if(file_path.rfind(".snu") == file_path.length() - 4)
			return parse_snu_DSGraph(file_path);
		else if(file_path.rfind(".snap") == file_path.length() - 5)
			return parse_snap_DSGraph(file_path);
		else if(file_path.rfind(".net") == file_path.length() - 4)
			return parse_net_DSGraph(file_path);
		// else if
		return NULL; // failed
	}

	USGraph *parse_snu_USGraph(std::string file_path) {
		std::ifstream infile(file_path);
		std::string line;
		USGraph *graph = new USGraph();
		Graph::Eid eid = 0;

		while(getline(infile, line)) {
			std::istringstream iss(line);

			std::string sign;
			iss >> sign;
			if(sign == "t") {}
			else if(sign == "v") {
				Graph::Vid id;
				Graph::Vlabel label;
				std::vector <Graph::Vlabel> label_vector;

				iss >> id;
				while(iss >> label) label_vector.push_back(label);
				if(graph->add_vertex(id, &label_vector)) { // error
					delete graph;
					return NULL;
				}
			}
			else if(sign == "e") {
				Graph::Vid from, to;
				Graph::Elabel label;
				std::vector<Graph::Elabel> label_vector;

				iss >> from >> to;
				while(iss >> label) label_vector.push_back(label);
				if(graph->add_edge(eid++, &label_vector, from, to, 1)) { // error
					delete graph;
					return NULL;
				}
			}
			else { // error
				delete graph;
				return NULL;
			}
		}

		return graph;
	}

	USGraph *parse_snap_USGraph(std::string file_path) {
		std::ifstream infile(file_path);
		std::string line;
		USGraph *graph = new USGraph();
		std::unordered_set <int> set;
		Graph::Eid eid = 0;

		while(getline(infile, line)) {
			std::istringstream iss(line);

			if(line.find("#") != std::string::npos)
				continue;

			Graph::Vid from, to;
			iss >> from >> to;

			if(!set.count(from)) {
				set.insert(from);
				graph->add_vertex(from, 0, NULL);
			}
			if(!set.count(to)) {
				set.insert(to);
				graph->add_vertex(to, 0, NULL);
			}

			// add edge
			graph->add_edge(eid++, 0, NULL, from, to, 1);
		}

		return graph;
	}

	USGraph *parse_USGraph(std::string file_path) {
		if(file_path.rfind(".snu") == file_path.length() - 4)
			return parse_snu_USGraph(file_path); // error
		else if(file_path.rfind(".snap") == file_path.length() - 5)
			return parse_snap_USGraph(file_path); // error
		else if(file_path.rfind(".net") == file_path.length() - 4)
			return NULL; // error
		// else if
		return NULL; // failed
	}
}
