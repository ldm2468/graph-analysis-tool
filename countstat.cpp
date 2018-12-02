#include "countstat.h"

namespace snu {
	
	void count_stat(USGraph *graph, USResult *result) {
		unsigned long long s = 0, z = 0, t = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			unsigned long long degree = it->second->indegree;
			s += degree * (degree - 1) / 2;
			z += degree * (degree - 1) * (degree - 2) / 6;

			Graph::Vertex *u = it->second;
			for(auto it1 = it->second->edges.begin(); it1 != it->second->edges.end(); it1++) {
				Graph::Vertex *v = (*it1)->to;
				if(u != v) {
					auto it2 = it1;
					for(it2++; it2 != it->second->edges.end(); it2++) {
						Graph::Vertex *w = (*it2)->to;
						if(u != w && v != w && graph->is_connected.count(std::make_pair(v->id, w->id)))
							t++;
					}
				}
			}
		}
		result->wedge_count = s;
		result->claw_count = z;
		result->triangle_count = t / 3;

		result->countstat = true;
	}
}