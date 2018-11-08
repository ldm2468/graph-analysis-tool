#include "basicstat.h"
#include "graph.h"
#include <unordered_set>

namespace snu {

	void basic_stat(DSGraph *graph, DSResult *result) {
		unsigned long long n = graph->id_to_vertex.size();
		unsigned long long m = graph->id_to_edge.size();

		result->size = n; // n
		result->volume = m; // m
		result->avg_degree = (double)m / n; // not defined well, m / n
		result->fill = (double)m / (n * n); // assume there is loop

		unsigned long long max_indegree = 0;
		unsigned long long max_outdegree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			max_indegree = std::max(max_indegree, it->second->indegree);
			max_outdegree = std::max(max_outdegree, it->second->edges.size());
		}
		result->max_indegree = max_indegree;
		result->max_outdegree = max_outdegree;
		
		result->reciprocity = 0; // TODO
		result->negativity = (double)graph->negative_edge_num / m;

		result->lcc = 0; // TODO
		result->diameter = 0; // TODO
	}

	void basic_stat(USGraph *graph, USResult *result) {
		unsigned int n = graph->id_to_vertex.size();
		unsigned int m = graph->id_to_edge.size();

		result->size = n; // n
		result->volume = m; // m
		result->avg_degree = 2.0 * m / n; // 2 * m / n
		result->fill = 2.0 * m / (n * (n + 1)); // assume there is loop
		// indegree == outdegree
		unsigned long long max_degree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			max_degree = std::max(max_degree, it->second->indegree);
		result->max_degree = max_degree;

		result->negativity = (double)graph->negative_edge_num / m;

		result->lcc = 0; // TODO
		result->diameter = 0; // TODO
	}
}
