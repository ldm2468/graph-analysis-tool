#ifndef PLOT_H
#define PLOT_H

#include "graph.h"
#include "graph_plot.h"
#include <stdio.h>

namespace snu {
	std::string *make_plot(DSGraph *graph, std::string plot_name);
	std::string *make_plot(USGraph *graph, std::string plot_name);
}

#endif // PLOT_H
