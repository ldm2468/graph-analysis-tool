#ifndef STAT_H
#define STAT_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))

namespace snu {

	typedef struct DSResult {
		/* basic satistics */
		unsigned int size; // number of vertices
		unsigned int volume; // number of edges
		unsigned int num_vlabel; // number of vertex label
		unsigned int num_elabel; // number of edge label
		double density; // m / n^2, directed graph with loops
		unsigned int max_indegree; // maximum indegree
		unsigned int max_outdegree; // maximum outdegree
		// size of vertex label is defined as number of vertices having that label
		unsigned int max_vlabel_size; // maximum size of vertex label
		unsigned int max_elabel_size; // maximum size of edge label
		double reciprocity; // only defined in directed graph
		double negativity; // ratio of nagative edges

		/* connectivity statistics */
		unsigned int num_scc; // number of strongly connected components
		unsigned int num_wcc; // number of weakly connected components
		unsigned int size_lscc; // largest size of strongly connected components
		unsigned int size_lwcc; // largest size of weakly connected components

		/* statistic check */
		bool basicstat;
		bool connectstat;
	} DSResult;

	typedef struct USResult {
		/* basic statistics */
		unsigned int size; // number of vertices
		unsigned int volume; // number of edges
		unsigned int num_vlabel; // number of vertex label
		unsigned int num_elabel; // number of edge label
		double density; // 2m / (N * (N + 1)), undirected graph with loops
		double avg_degree; // average degree, 2m / n
		unsigned int max_degree; // maximum degree
		// size of vertex label is defined as number of vertices having that label
		unsigned int max_vlabel_size; // maximum size of vertex label
		unsigned int max_elabel_size; // maximum size of edge label
		double negativity; // ratio of nagative edges
		
		/* connectivity statistics */
		unsigned int num_cc; // number of connected components
		unsigned int size_lcc; // largest size of connected components
		unsigned int diameter; // longest shortest paths

		/* counting statistics */
		unsigned long long wedge_count; // number of wedges
		unsigned long long claw_count; // number of claws
		unsigned long long triangle_count; // number of triangles

		/* stat check */
		bool basicstat;
		bool connectstat;
		bool countstat;
	} USresult;

	void init_stat(DSResult *result);
	void init_stat(USResult *result);
}

#endif // STAT_H