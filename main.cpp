#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library
	snu::DSGraph *graph = snu::parse_DSGraph("example.snu");
	struct snu::DSResult result;

	if(snu::basic_stat(graph, &result))
		printf("error\n");

	printf("size           : %u\n", result.size);
	printf("volume         : %u\n", result.volume);
	printf("avg_degree     : %lf\n", result.avg_degree);
	printf("fill           : %lf\n", result.fill);
	printf("max_indegree   : %u\n", result.max_indegree);
	printf("max_outdegree  : %u\n", result.max_outdegree);
	printf("reciprocity    : %lf\n", result.reciprocity);
	printf("negativity     : %lf\n", result.negativity);
	printf("lcc            : %u\n", result.lcc);
	printf("four_tour_count: %llu\n", result.four_tour_count);
	printf("diameter       : %u\n", result.diameter);

	return 0;
}
