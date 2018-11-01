#include "basicstat.h"
#include "graph.h"
#include <unordered_set>

namespace snu {

	int basic_stat(DSGraph *graph, DSResult *result) {
		
		/*std::unordered_set <Graph::Vertex *> check;
		
		int n = graph->id_to_vertex.size();
		int m = graph->id_to_edge.size();

		result.size = n;
		result.volume = m;
		result.avg_degree = 2.0 * m / n;
		result.fill = (double)m / (n * n); // TODO: 그래프 유형에 따라 fill이 달라지므로 이후에 처리해야 함

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			Graph::Vertex *v = it->second;
			v->edges.size();
		}*/
		*result = {
			.size = graph->id_to_vertex.size(),
			.volume = graph->id_to_edge.size(),
			.avg_degree = 0,
			.fill = 0,
			.max_indegree = 0,
			.max_outdegree = 0,
			.reciprocity = 0,
			.negativity = 0,
			.lcc = 0,
			.four_tour_count = 0,
			.diameter = 0,
		};
		return 0;
	}

	int basic_stat(USGraph *graph, USResult *result) {
		*result = {
			.size = 0,
			.volume = 0,
			.avg_degree = 0,
			.fill = 0,
			.max_degree = 0,
			.negativity = 0,
			.lcc = 0,
			.wedge_count = 0,
			.claw_count = 0,
			.triangle_count = 0,
			.square_count = 0,
			.four_tour_count = 0,
			.diameter = 0,
		};
		return 0;
	}
}
