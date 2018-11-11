#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library
	snu::DSGraph *graph = snu::parse_DSGraph("example.snu");
	struct snu::DSResult result;

	snu::make_plot(graph); // make plot
	
	snu::init_stat(&result);
	snu::basic_stat(graph, &result);
	snu::count_stat(graph, &result);
	
	snu::make_html("stat.html", &result); // make html

	return 0;
}
