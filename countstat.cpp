#include "countstat.h"
#include <algorithm>

namespace snu {
	
	void count_stat(USGraph *graph, USResult *result) {
		unsigned long long s = 0, z = 0, t = 0;
		
		std::vector <std::pair <unsigned int, Graph::Vertex *> > vec;

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++) {
			unsigned int degree = it->second->indegree;
			s += (unsigned long long) degree * (degree - 1) / 2;
			z += (unsigned long long) degree * (degree - 1) * (degree - 2) / 6;
			vec.push_back(std::make_pair(degree, it->second));
		}

		result->wedge_count = s;
		result->claw_count = z;
		
		std::sort(vec.begin(), vec.end());

		int size = vec.size();
		for(int i = 0; i < size; i++)
			vec[i].second->temp = new int(i); // rank

		char *check = new char[size]();

		for(int i = 0; i < size; i++) {
			Graph::Vertex *v = vec[i].second;
			int vrank = *(int *) v->temp;

			for(auto it = v->edges.begin(); it != v->edges.end(); it++) {
				Graph::Vertex *u = v == (*it)->to ? (*it)->from : (*it)->to;
				int urank = *(int *) u->temp;
				check[urank] = 1;
			}

			for(auto it = v->edges.begin(); it != v->edges.end(); it++) {
				Graph::Vertex *u = v == (*it)->to ? (*it)->from : (*it)->to;
				int urank = *(int *) u->temp;
				if(vrank < urank)
					for(auto it2 = u->edges.begin(); it2 != u->edges.end(); it2++) {
						Graph::Vertex *w = u == (*it2)->to ? (*it2)->from : (*it2)->to;
						int wrank = *(int *) w->temp;
						if(check[wrank]) t++;
					}
			}
			
			for(auto it = v->edges.begin(); it != v->edges.end(); it++) {
				Graph::Vertex *u = v == (*it)->to ? (*it)->from : (*it)->to;
				int urank = *(int *) u->temp;
				check[urank] = 0;
			}
		}
		
		for(int i = 0; i < size; i++)
			delete (int *) vec[i].second->temp;
		
		delete check;

		result->triangle_count = t / 3;

		result->countstat = true;
	}
}