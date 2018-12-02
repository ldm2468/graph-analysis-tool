#include "connectstat.h"
#include <queue>

namespace snu {
	/*
	unsigned long long BFS(Graph::Vertex *start) {
		unsigned int cnt = 0;
		char visit = start->visit = 1 - start->visit;
		std::queue <Graph::Vertex *> q;

		q.push(start);

		while(!q.empty()) {
			Graph::Vertex *curr = q.front();
			q.pop();
			cnt++;

			for(auto it = curr->edges.begin(); it != curr->edges.end(); it++) {
				Graph::Vertex *next = (*it)->to;

				if(next->visit != visit) {
					next->visit = visit;
					q.push(next);
				}
			}
		}

		return cnt;
	}*/
	
	void connect_stat(DSGraph *graph, DSResult *result) {
	
	}

	void connect_stat(USGraph *graph, USResult *result) {

		/*
			result->lcc = 0; // initialize
		graph->visit = 1 - graph->visit; // change visit state
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			if(it->second->visit != graph->visit) {
				unsigned int conn_component = BFS(it->second);
				result->lcc = MAX(result->lcc, conn_component);
			}
		}
		*/
		// result->diameter = 0; // TODO
	}
}