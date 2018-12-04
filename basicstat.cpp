#include "basicstat.h"

namespace snu {

	void basic_stat(DSGraph *graph, DSResult *result) {
		unsigned int n = graph->id_to_vertex.size();
		unsigned int m = graph->id_to_edge.size();

		result->size = n;
		result->volume = m;
		result->num_vlabel = graph->vlabel_to_class.size();
		result->num_elabel = graph->elabel_to_class.size();
		result->density = (double) m / (n * n); // assume there is loop

		unsigned int max_indegree = 0;
		unsigned int max_outdegree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			max_indegree = MAX(max_indegree, it->second->indegree);
			max_outdegree = MAX(max_outdegree, it->second->edges.size());
		}
		result->max_indegree = max_indegree;
		result->max_outdegree = max_outdegree;
		
		unsigned int max_vlabel_size = 0;
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			max_vlabel_size = MAX(max_vlabel_size, it->second->vertices.size());
		result->max_vlabel_size = max_vlabel_size;

		unsigned int max_elabel_size = 0;
		for(auto it = graph->elabel_to_class.begin(); it != graph->elabel_to_class.end(); it++)
			max_elabel_size = MAX(max_elabel_size, it->second->edges.size());
		result->max_elabel_size = max_elabel_size;

		unsigned int cnt = 0;
		for(auto it = graph->id_to_edge.begin(); it != graph->id_to_edge.end(); it++) {
			Graph::Vid from = it->second->from->id, to = it->second->to->id;
			if(graph->is_connected.count(std::make_pair(to, from))) cnt++;
		}
		result->reciprocity = (double) cnt / m;

		result->negativity = (double) graph->negative_edge_num / m;

		result->basicstat = true;
	}

	void basic_stat(USGraph *graph, USResult *result) {
		unsigned int n = graph->id_to_vertex.size();
		unsigned int m = graph->id_to_edge.size();

		result->size = n; // n
		result->volume = m; // m
		result->num_vlabel = graph->vlabel_to_class.size();
		result->num_elabel = graph->elabel_to_class.size();
		result->density = 2.0 * m / (n * (n + 1)); // assume there is loop
		result->avg_degree = 2.0 * m / n; // 2 * m / n
		
		unsigned int max_degree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			max_degree = MAX(max_degree, it->second->indegree); // indegree == outdegree
		result->max_degree = max_degree;

		unsigned int max_vlabel_size = 0;
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			max_vlabel_size = MAX(max_vlabel_size, it->second->vertices.size());
		result->max_vlabel_size = max_vlabel_size;

		unsigned int max_elabel_size = 0;
		for(auto it = graph->elabel_to_class.begin(); it != graph->elabel_to_class.end(); it++)
			max_elabel_size = MAX(max_elabel_size, it->second->edges.size());
		result->max_elabel_size = max_elabel_size;

		result->negativity = (double) graph->negative_edge_num / m;

		result->basicstat = true;
	}
}
