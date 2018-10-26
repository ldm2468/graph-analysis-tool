#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library
	snu::DSGraph *graph = new snu::DSGraph();
	struct snu::DSResult result;

	if(snu::basic_stat(graph, &result))
		printf("error\n");

	return 0;
}
