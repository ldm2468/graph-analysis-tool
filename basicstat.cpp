#include "basicstat.h"
#include <unordered_set>
#include <queue>
#define MAX(x, y) ((x) > (y) ? (x) : (y))

namespace snu {

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
	}

	void basic_stat(DSGraph *graph, DSResult *result) {
		unsigned int n = graph->id_to_vertex.size();
		unsigned int m = graph->id_to_edge.size();

		result->size = n; // n
		result->volume = m; // m
		result->avg_degree = (double)m / n; // not defined well, m / n
		result->fill = (double)m / (n * n); // assume there is loop

		unsigned int max_indegree = 0;
		unsigned int max_outdegree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			max_indegree = MAX(max_indegree, it->second->indegree);
			max_outdegree = MAX(max_outdegree, it->second->edges.size());
		}
		result->max_indegree = max_indegree;
		result->max_outdegree = max_outdegree;
		
		unsigned int cnt = 0;
		for(auto it = graph->id_to_edge.begin(); it != graph->id_to_edge.end(); it++) {
			Graph::Vid from = it->second->from->id, to = it->second->to->id;
			if(graph->is_connected.count(std::make_pair(to, from))) cnt++;
		}
		result->reciprocity = (double)cnt / m;

		result->negativity = (double)graph->negative_edge_num / m;

		result->lcc = 0; // initialize
		graph->visit = 1 - graph->visit; // change visit state
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			if(it->second->visit != graph->visit) {
				unsigned int conn_component = BFS(it->second);
				result->lcc = MAX(result->lcc, conn_component);
			}
		}

		// result->diameter = 0; // TODO

		result->basicstat = true;
	}

	void basic_stat(USGraph *graph, USResult *result) {
		unsigned int n = graph->id_to_vertex.size();
		unsigned int m = graph->id_to_edge.size();

		result->size = n; // n
		result->volume = m; // m
		result->avg_degree = 2.0 * m / n; // 2 * m / n
		result->fill = 2.0 * m / (n * (n + 1)); // assume there is loop
		// indegree == outdegree
		unsigned int max_degree = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			max_degree = MAX(max_degree, it->second->indegree);
		result->max_degree = max_degree;

		result->negativity = (double)graph->negative_edge_num / m;

		result->lcc = 0; // initialize
		graph->visit = 1 - graph->visit; // change visit state
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			if(it->second->visit != graph->visit) {
				unsigned int conn_component = BFS(it->second);
				result->lcc = MAX(result->lcc, conn_component);
			}
		}

		// result->diameter = 0; // TODO

		result->basicstat = true;
	}
}
