#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html.h"

namespace snu {
  
	void make_html(const char *name, DSResult *result, Plot *plot) {
		char *real_name = (char *)malloc(strlen(name) + 6);
		sprintf(real_name, "%s.html", name);
		FILE *fp = fopen(real_name, "w");
		free(real_name);

		fprintf(fp, "\
		<!DOCTYPE html>\
		<html>\
			<head>\
				<meta charset = \"utf-8\">\
				<title>SNU Graph Analysis Tool</title>\
				<style type=\"text/css\">\
					h1{\
						text-indent: 1em;\
					}\
					h2{\
						text-indent: 2em;\
					}\
					h3{\
						text-indent: 4em;\
					}\
				</style>\
			</head>\
			<body>\
				<h1><p>SNU Graph Analysis Tool</p></h1>");

		if(result) {
			if(result->basicstat)
				fprintf(fp, "\
					<h2>\
						(1) Basic statistics\
					</h2>\
					<h3>\
					<p> size = %u </p>\
					<p> volume = %u </p>\
					<p> avg_degree = %lf </p>\
					<p> density(fill) = %lf </p>\
					<p> max_indegree = %u </p>\
					<p> max_outdegree = %u </p>\
					<p> reciprocity = %lf </p>\
					<p> negativity = %lf </p>\
					<p> largest connected component = %u </p>\
					</h3>\
					", result->size, result->volume, result->avg_degree, result->fill
					, result->max_indegree, result->max_outdegree, result->reciprocity
					, result->negativity, result->lcc);


			if(result->countstat)
				fprintf(fp, "\
					<h2>\
						(2) Count statistics\
					</h2>");
		}

		if(plot && plot->makeplot)
			fprintf(fp, "\
					</h2>\
					<h2>\
						(3) Statistics Image\
					</h2>\
					<h3>\
					<p> label-vertex image </p>\
					<img src=\"pyplot/%d_label-vertex.png\" width=\"400\" alt=\"label-vertex image\">\
					<img src=\"pyplot/%d_label-vertex_log.png\" width=\"400\" alt=\log scale label-vertex image\">\
					</h3>\
					<h3>\
					<p> indegree image </p>\
					<img src=\"pyplot/%d_indegree.png\" width=\"400\" alt=\"indegree image\">\
					<img src=\"pyplot/%d_indegree_log.png\" width=\"400\" alt=\"log scale indegree image\">\
					</h3>\
					<h3>\
					<p> outdegree image </p>\
					<img src=\"pyplot/%d_outdegree.png\" width=\"400\" alt=\"outdegree image\">\
					<img src=\"pyplot/%d_outdegree_log.png\" width=\"400\" alt=\"log scale outdegree image\">\
					</h3>\
				</body>\
			</html>\
			", plot->id, plot->id, plot->id, plot->id, plot->id, plot->id);
		
		fclose(fp);
	}

	void make_html(const char *name, USResult *result, Plot *plot) {
		char *real_name = (char *)malloc(strlen(name) + 6);
		sprintf(real_name, "%s.html", name);
		FILE *fp = fopen(real_name, "w");
		free(real_name);
		
		fprintf(fp, "\
		<!DOCTYPE html>\
		<html>\
			<head>\
				<meta charset = \"utf-8\">\
				<title>SNU Graph Analysis Tool</title>\
				<style type=\"text/css\">\
					h1{\
						text-indent: 1em;\
					}\
					h2{\
						text-indent: 2em;\
					}\
					h3{\
						text-indent: 4em;\
					}\
				</style>\
			</head>\
			<body>\
				<center><h1><p>SNU Graph Analysis Tool</p></h1></center>");

		if(result) {
			if(result->basicstat)
				fprintf(fp, "\
					<h2>\
						(1) Basic statistics\
					</h2>\
					<h3>\
					<p> size = %u </p>\
					<p> volume = %u </p>\
					<p> avg_degree = %lf </p>\
					<p> density(fill) = %lf </p>\
					<p> max_degree = %u </p>\
					<p> negativity = %lf </p>\
					<p> largest connected component = %u </p>\
					</h3>\
					", result->size, result->volume, result->avg_degree, result->fill
					, result->max_degree, result->negativity, result->lcc);


			if(result->countstat)
				fprintf(fp, "\
					<h2>\
						(2) Count statistics\
					</h2>\
					<h3>\
					<p> wedge_count = %llu </p>\
					<p> claw_count = %llu </p>\
					</h3>\
					", result->wedge_count, result->claw_count);
		}

		if(plot && plot->makeplot)
			fprintf(fp, "\
					</h2>\
					<h2>\
						(3) Statistics Image\
					</h2>\
					<h3>\
					<p> label-vertex image </p>\
					<img src=\"pyplot/%d_label-vertex.png\" width=\"400\" alt=\"label-vertex image\">\
					<img src=\"pyplot/%d_label-vertex_log.png\" width=\"400\" alt=\log scale label-vertex image\">\
					</h3>\
					<h3>\
					<p> degree image </p>\
					<img src=\"pyplot/%d_degree.png\" width=\"400\" alt=\"degree image\">\
					<img src=\"pyplot/%d_degree_log.png\" width=\"400\" alt=\"log scale degree image\">\
					</h3>\
				</body>\
			</html>\
			", plot->id, plot->id, plot->id, plot->id);
		
		fclose(fp);
	}
}
