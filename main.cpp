#include <stdio.h>
#include "snugal.h"

int main(int argc, char *argv[]) {

	// test library

	snu::DSGraph *dsg1 = snu::parse_DSGraph("data/example.snu");
	snu::DSResult dsr1;
	snu::Plot plot1;
	snu::init_stat(&dsr1);
	snu::basic_stat(dsg1, &dsr1);
	snu::connect_stat(dsg1, &dsr1);
	snu::init_plot(&plot1);
	snu::make_plot(dsg1, &plot1);
	snu::make_html("example", &dsr1, &plot1);
	delete dsg1;

	snu::USGraph *usg1 = snu::parse_USGraph("data/com-dblp_label.snu");
	snu::USResult usr1;
	snu::Plot plot2;
	snu::init_stat(&usr1);
	snu::basic_stat(usg1, &usr1);
	snu::connect_stat(usg1, &usr1);
	snu::init_plot(&plot2);
	snu::make_plot(usg1, &plot2);
	snu::make_html("com-dblp_label", &usr1, &plot2);
	delete usg1;

	snu::DSGraph *dsg2 = snu::parse_DSGraph("data/web-Google_label.snu");
	snu::DSResult dsr2;
	snu::Plot plot3;
	snu::init_stat(&dsr2);
	snu::basic_stat(dsg2, &dsr2);
	snu::connect_stat(dsg2, &dsr2);
	snu::init_plot(&plot3);
	snu::make_plot(dsg2, &plot3);
	snu::make_html("web-Google_label", &dsr2, &plot3);
	delete dsg2;

	snu::USGraph *usg2 = snu::parse_USGraph("data/as-skitter_label.snu");
	snu::USResult usr2;
	snu::Plot plot4;
	snu::init_stat(&usr2);
	snu::basic_stat(usg2, &usr2);
	snu::connect_stat(usg2, &usr2);
	snu::init_plot(&plot4);
	snu::make_plot(usg2, &plot4);
	snu::make_html("as-skitter_label", &usr2, &plot4);
	delete usg2;

	snu::DSGraph *dsg3 = snu::parse_DSGraph("data/web-BerkStan.snap");
	snu::DSResult dsr3;
	snu::Plot dsplot;
	snu::init_stat(&dsr3);
	snu::basic_stat(dsg3, &dsr3);
	snu::connect_stat(dsg3, &dsr3);
	snu::init_plot(&dsplot);
	snu::make_plot(dsg3, &dsplot);
	snu::make_html("web-BerkStan", &dsr3, &dsplot);
	delete dsg3;

	snu::USGraph *usg3 = snu::parse_USGraph("data/ca-AstroPh.snap");
	snu::USResult usr3;
	snu::Plot usplot;
	snu::init_stat(&usr3);
	snu::basic_stat(usg3, &usr3);
	snu::connect_stat(usg3, &usr3);
	snu::count_stat(usg3, &usr3);
	snu::init_plot(&usplot);
	snu::make_plot(usg3, &usplot);
	snu::make_html("ca-AstroPh", &usr3, &usplot);
	delete usg3;

	return 0;
}
