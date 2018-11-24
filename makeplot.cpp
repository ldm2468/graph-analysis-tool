#include "makeplot.h"
#include <fstream>
#include <vector>
#include <algorithm>

namespace snu {

	void make_plot(DSGraph *graph, Plot *plot) {
		std::ofstream out;

		/* label-vertex */
		out.open("./pyplot/label-vertex.txt");

		unsigned int n = graph->id_to_vertex.size();
		typedef std::pair <unsigned int, std::string *> vectype;
		std::vector <vectype> vec;
		vec.reserve(n);
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++) {
			auto vlabel = *(it->second);
			vec.push_back(make_pair(vlabel.vertices.size(), &vlabel.label));
		}

		std::sort(vec.begin(), vec.end(), [](vectype a, vectype b) { return a.first > b.first; });

		for(auto it = vec.begin(); it != vec.end(); it++)
			out << *(it->second) << " " << it->first << std::endl;

		out.close();

		/* indegree */
		out.open("./pyplot/indegree.txt");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			out << (*it->second).indegree << " ";

		out.close();

		/* outdegree */
		out.open("./pyplot/outdegree.txt");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			out << (*it->second).edges.size() << " ";

		out.close();
	}

	void make_plot(USGraph *graph, Plot *plot) {
		std::ofstream out;

		/* label-vertex */
		out.open("./pyplot/label-vertex.txt");

		unsigned int n = graph->id_to_vertex.size();
		typedef std::pair <unsigned int, std::string *> vectype;
		std::vector <vectype> vec;
		vec.reserve(n);
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++) {
			auto vlabel = *(it->second);
			vec.push_back(make_pair(vlabel.vertices.size(), &vlabel.label));
		}

		std::sort(vec.begin(), vec.end(), [](vectype a, vectype b) { return a.first > b.first; });

		for(auto it = vec.begin(); it != vec.end(); it++)
			out << *(it->second) << " " << it->first << std::endl;

		out.close();

		/* degree */
		out.open("./pyplot/degree.txt");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			out << (*it->second).indegree << " ";

		out.close();
	}
}
