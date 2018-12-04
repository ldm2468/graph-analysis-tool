#include "connectstat.h"
#include <queue>
#include <stack>
#include <vector>

namespace snu {

	void connect_stat(DSGraph *graph, DSResult *result) {
	
		typedef struct Vertex_info {
			std::vector <Graph::Edge *> reverse_edges; // to -> from
			bool visit; // default: false
		} Vertex_info;

		// create additional information for BFS and DFS
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			it->second->temp = new Vertex_info();
		for(auto it = graph->id_to_edge.begin(); it != graph->id_to_edge.end(); it++) {
			Graph::Edge *edge = it->second;
			Vertex_info *info = (Vertex_info *)edge->to->temp;
			info->reverse_edges.push_back(edge);
		}

		/* SCC */
		typedef class Kosaraju {
		public:
			static void first(Graph::Vertex *start, std::stack <Graph::Vertex *> *s) {
				std::stack <Graph::Vertex *> s1;
				std::stack <std::list <Graph::Edge *>::iterator> s2;
				s1.push(start);
				s2.push(start->edges.begin());
				s2.push(start->edges.end());

				Vertex_info *start_info = (Vertex_info *)start->temp;
				start_info->visit = true;

				while(!s1.empty()) {
					auto end = s2.top();
					s2.pop();
					auto it = s2.top();
					s2.pop();

					for(; it != end; it++) {
						Graph::Vertex *next = (*it)->to;
						Vertex_info *next_info = (Vertex_info *)next->temp;

						if(!next_info->visit) {
							next_info->visit = true;
							auto it2 = it;
							s2.push(++it2);
							s2.push(end);
							s1.push(next);
							s2.push(next->edges.begin());
							s2.push(next->edges.end());
							break;
						}
					}

					if(it == end) {
						s->push(s1.top());
						s1.pop();
					}
				}
			}

			static unsigned int second(Graph::Vertex *start) {
				unsigned int cnt = 0;
				Vertex_info *now_info, *next_info;
				std::queue <Graph::Vertex *> q;

				now_info = (Vertex_info *)start->temp;
				now_info->visit = false;
				q.push(start);

				while(!q.empty()) {
					Graph::Vertex *now = q.front();
					q.pop();
					cnt++;
					now_info = (Vertex_info *)now->temp;

					// reverse edges
					for(auto it = now_info->reverse_edges.begin(); it != now_info->reverse_edges.end(); it++) {
						Graph::Vertex *next = (*it)->from;
						next_info = (Vertex_info *)next->temp;

						if(next_info->visit) {
							next_info->visit = false;
							q.push(next);
						}
					}
				}

				return cnt;
			}

		} Kosaraju;

		std::stack <Graph::Vertex *> s;

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			Vertex_info *info = (Vertex_info *)it->second->temp;
			if(!info->visit)
				Kosaraju::first(it->second, &s);
		}

		result->num_scc = 0;
		result->size_lscc = 0;

		unsigned int hab = 0;

		while(!s.empty()) {
			Graph::Vertex *v = s.top();
			s.pop();
			Vertex_info *info = (Vertex_info *)v->temp;
			
			if(info->visit) {
				result->num_scc++;
				unsigned int size_scc = Kosaraju::second(v);
				hab += size_scc;
				result->size_lscc = MAX(result->size_lscc, size_scc);
			}
		}

		/* WCC */
		typedef class WCC {
		public:
			static unsigned int bfs(Graph::Vertex *start) {
				unsigned int cnt = 0;
				Vertex_info *now_info, *next_info;
				std::queue <Graph::Vertex *> q;

				now_info = (Vertex_info *)start->temp;
				now_info->visit = true;
				q.push(start);

				while(!q.empty()) {
					Graph::Vertex *now = q.front();
					q.pop();
					cnt++;
					now_info = (Vertex_info *)now->temp;

					// edges
					for(auto it = now->edges.begin(); it != now->edges.end(); it++) {
						Graph::Vertex *next = (*it)->to;
						next_info = (Vertex_info *)next->temp;

						if(!next_info->visit) {
							next_info->visit = true;
							q.push(next);
						}
					}

					// reverse edges
					for(auto it = now_info->reverse_edges.begin(); it != now_info->reverse_edges.end(); it++) {
						Graph::Vertex *next = (*it)->from;
						next_info = (Vertex_info *)next->temp;

						if(!next_info->visit) {
							next_info->visit = true;
							q.push(next);
						}
					}
				}

				return cnt;
			}
		} WCC;

		result->num_wcc = 0;
		result->size_lwcc = 0;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			Vertex_info *info = (Vertex_info *)it->second->temp;
			if(!info->visit) {
				result->num_wcc++;
				unsigned int size_wcc = WCC::bfs(it->second);
				result->size_lwcc = MAX(result->size_lwcc, size_wcc);
			}
		}

		// delete additional information created before
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			delete (Vertex_info *)it->second->temp;

		result->connectstat = true;
	}

	void connect_stat(USGraph *graph, USResult *result) {

		typedef struct First_info {
			Graph::Vertex *farthest;
			unsigned int size_cc;
		} First_info;

		typedef struct Vertex_info {
			unsigned int dist;
			bool visit;
		} Vertex_info;

		typedef class BFS {
		public:
			static First_info first(Graph::Vertex *start) {
				unsigned int cnt = 0;
				Graph::Vertex *now = start;
				Vertex_info *now_info, *next_info;
				std::queue <Graph::Vertex *> q;

				now_info = (Vertex_info *)now->temp;
				now_info->visit = true;
				now_info->dist = 0;
				q.push(start);

				while(!q.empty()) {
					now = q.front();
					q.pop();
					cnt++;
					now_info = (Vertex_info *)now->temp;

					for(auto it = now->edges.begin(); it != now->edges.end(); it++) {
						Graph::Vertex *next = now == (*it)->to ? (*it)->from : (*it)->to;
						next_info = (Vertex_info *)next->temp;

						if(!next_info->visit) {
							next_info->visit = true;
							next_info->dist = now_info->dist + 1;
							q.push(next);
						}
					}
				}

				return First_info {now, cnt};
			}

			static unsigned int second(Graph::Vertex *start) {
				Vertex_info *now_info, *next_info;
				std::queue <Graph::Vertex *> q;

				now_info = (Vertex_info *)start->temp;
				now_info->visit = false;
				now_info->dist = 0;
				q.push(start);

				while(!q.empty()) {
					Graph::Vertex *now = q.front();
					q.pop();
					now_info = (Vertex_info *)now->temp;

					for(auto it = now->edges.begin(); it != now->edges.end(); it++) {
						Graph::Vertex *next = now == (*it)->to ? (*it)->from : (*it)->to;
						next_info = (Vertex_info *)next->temp;

						if(next_info->visit) {
							next_info->visit = false;
							next_info->dist = now_info->dist + 1;
							q.push(next);
						}
					}
				}

				return now_info->dist;
			}

		} BFS;

		// create additional information for BFS
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			it->second->temp = new Vertex_info(); // temp as visit

		result->num_cc = 0;
		result->size_lcc = 0;
		std::vector <Graph::Vertex *> vertices;
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			if(!(*(char *)it->second->temp)) {
				result->num_cc++;
				First_info info = BFS::first(it->second);
				vertices.push_back(info.farthest);
				result->size_lcc = MAX(result->size_lcc, info.size_cc);
			}
		}
		
		result->diameter = 0;
		for(auto it = vertices.begin(); it != vertices.end(); it++) {
			unsigned int dist = BFS::second(*it);
			result->diameter = MAX(result->diameter, dist);
		}

		// delete additional information created before
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			delete (Vertex_info *)it->second->temp;
		
		result->connectstat = true;
	}
}
