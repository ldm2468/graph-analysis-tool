#include "basicstat.h"
#include "graph.h"
#include <unordered_set>

namespace snu {
	/*
	int size; // number of vertices
	int volume; // number of edges
	double avg_degree; // average degree
	double fill; // based on directed graph, m / n^2, loop? yes, nultiedge? no
	int max_degree; // maximum degree
	int lcc; // largest connected component
	int diameter; // diameter of graph */

	void basicstat(Graph *graph, struct basic_result result) {
		std::unordered_set <Graph::Vertex *> check;
		
		int n = graph->id_to_vertex.size();
		int m = graph->id_to_edge.size();

		result.size = n;
		result.volume = m;
		result.avg_degree = 2.0 * m / n;
		result.fill = (double)m / (n * n); // TODO: 그래프 유형에 따라 fill이 달라지므로 이후에 처리해야 함

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			Graph::Vertex *v = it->second;
			v->edges.size();
		}
	}
}
