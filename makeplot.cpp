#include "makeplot.h"
#include "graph_plot.h"

namespace snu {

	void make_plot(DSGraph *graph, Plot *plot) {
		FILE *fp = fopen("./matlab_plot/label-vertex.txt", "w");

		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			fprintf(fp, "%s %llu\n", (*it->second).label.c_str(), (*it->second).vertices.size());

		fclose(fp);

		fp = fopen("./matlab_plot/indegree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%llu ", (*it->second).indegree);

		fclose(fp);

		fp = fopen("./matlab_plot/outdegree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%llu ", (*it->second).edges.size());

		fclose(fp);

		if(!graph_plotInitialize()) return; // error

		char name[10];
		sprintf(name, "%d", *plot);
		mwArray mw_name(name);
		graph_plot(mw_name);

		graph_plotTerminate();
	}

	void make_plot(USGraph *graph, Plot *plot) {
		FILE *fp = fopen("./matlab_plot/label-vertex.txt", "w");

		// descending order
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			fprintf(fp, "%s %llu\n", (*it->second).label.c_str(), (*it->second).vertices.size());

		fclose(fp);

		fp = fopen("./matlab_plot/degree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%llu ", (*it->second).indegree);

		fclose(fp);
		
		if(!graph_plotInitialize()) return; // error

		char name[10];
		sprintf(name, "%d", *plot);
		mwArray mw_name(name);
		graph_plot(mw_name);

		graph_plotTerminate();
	}
}
