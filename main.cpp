#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library
	snu::DSGraph *graph = snu::parse_DSGraph("example.snu");
	struct snu::DSResult result;

	snu::basic_stat(graph, &result);
	snu::count_stat(graph, &result);

	printf("/* basic_stat */\n");
	printf("size           : %llu\n", result.size);
	printf("volume         : %llu\n", result.volume);
	printf("avg_degree     : %lf\n", result.avg_degree);
	printf("fill           : %lf\n", result.fill);
	printf("max_indegree   : %llu\n", result.max_indegree);
	printf("max_outdegree  : %llu\n", result.max_outdegree);
	printf("reciprocity    : %lf\n", result.reciprocity);
	printf("negativity     : %lf\n", result.negativity);
	printf("lcc            : %llu\n", result.lcc);
	printf("diameter       : %llu\n", result.diameter);
	
	printf("/* count_stat */\n");
	printf("four_tour_count: %llu\n", result.four_tour_count);

	return 0;
}
