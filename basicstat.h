#ifndef BASICSTAT_H
#define BASICSTAT_H

namespace snu {

	struct basic_result {
		int size; // number of vertices
		int volume; // number of edges
		double avg_degree; // average degree
		double fill; // based on directed graph, m / n^2, loop? yes, nultiedge? no
		int max_degree; // maximum degree
		int lcc; // largest connected component
		int diameter; // diameter of graph
	};

	void basicstat(Graph *graph, struct basic_result result);
}

#endif // BASICSTAT_H
