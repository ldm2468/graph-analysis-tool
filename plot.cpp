#include <stdio.h>
#include "plot.h"

namespace snu {

	void make_plot(DSGraph *graph) {
		FILE *fp = fopen("./matlab_plot/label-vertex.txt", "w");

		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			fprintf(fp, "%s %d\n", (*it->second).label, (*it->second).vertices.size());
		
		fclose(fp);

		fp = fopen("./matlab_plot/indegree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%d ", (*it->second).indegree);
		
		fclose(fp);

		fp = fopen("./matlab_plot/outdegree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%d ", (*it->second).edges.size());
	
		fclose(fp);
	}

	void make_plot(USGraph *graph) {
		FILE *fp = fopen("./matlab_plot/label-vertex.txt", "w");

		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++)
			fprintf(fp, "%s %d\n", (*it->second).label, (*it->second).vertices.size());
		
		fclose(fp);

		fp = fopen("./matlab_plot/degree.txt", "w");

		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			fprintf(fp, "%d ", (*it->second).indegree);
		
		fclose(fp);
	}
}