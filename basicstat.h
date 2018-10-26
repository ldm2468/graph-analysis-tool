#ifndef BASICSTAT_H
#define BASICSTAT_H

namespace snu {

	struct DSResult {
		unsigned int size; // number of vertices
		unsigned int volume; // number of edges
		double avg_degree; // not defined well but calculate it as m / n
		double fill; // m / n^2, directed graph with loops
		unsigned int max_indegree; // maximum indegree
		unsigned int max_outdegree; // maximum outdegree
		double reciprocity; // only defined in directed graph
		double negativity;
		unsigned int lcc; // largest connected component
		unsigned int four_tour_count;
		unsigned int diameter; // diameter of graph
	};

	struct USResult {
		int size;
		int volume;
		double avg_degree; // average degree, 2m / n
		double fill; // 2m / (N * (N + 1)), undirected graph with loops
		int max_degree; // maximum degree
		double negativity;
		unsigned int lcc;
		unsigned int wedge_count;
		unsigned int claw_count;
		unsigned int triangle_count;
		unsigned int square_count;
		unsigned int four_tour_count;
		unsigned int diameter;
	};

	int basic_stat(class DSGraph *graph, DSResult *result);

	int basic_stat(class USGraph *graph, USResult *result);
}

#endif // BASICSTAT_H
