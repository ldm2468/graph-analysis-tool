#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library
	snu::DSGraph *graph1 = snu::parse_DSGraph("data/A96.net");
	snu::DSGraph *graph2 = snu::parse_DSGraph("data/as-skitter_label.snu");
	snu::DSGraph *graph3 = snu::parse_DSGraph("data/com-dblp_label.snu");
	snu::DSGraph *graph4 = snu::parse_DSGraph("data/example.snu");
	snu::DSGraph *graph5 = snu::parse_DSGraph("data/web-Google_label.snu");
	struct snu::DSResult result1, result2, result3, result4, result5;

	snu::init_stat(&result1);
	snu::init_stat(&result2);
	snu::init_stat(&result3);
	snu::init_stat(&result4);
	snu::init_stat(&result5);

	snu::basic_stat(graph1, &result1);
	snu::basic_stat(graph2, &result2);
	snu::basic_stat(graph3, &result3);
	snu::basic_stat(graph4, &result4);
	snu::basic_stat(graph5, &result5);

	snu::count_stat(graph1, &result1);
	snu::count_stat(graph2, &result2);
	snu::count_stat(graph3, &result3);
	snu::count_stat(graph4, &result4);
	snu::count_stat(graph5, &result5);

	snu::Plot *plot1 = snu::make_plot(graph1, "graph1");
	snu::Plot *plot2 = snu::make_plot(graph2, "graph2");
	snu::Plot *plot3 = snu::make_plot(graph3, "graph3");
	snu::Plot *plot4 = snu::make_plot(graph4, "graph4");
	snu::Plot *plot5 = snu::make_plot(graph5, "graph5");

	snu::make_html("graph1.html", &result1, plot1);
	snu::make_html("graph2.html", &result1, plot2);
	snu::make_html("graph3.html", &result1, plot3);
	snu::make_html("graph4.html", &result1, plot4);
	snu::make_html("graph5.html", &result1, plot5);

	return 0;
}
