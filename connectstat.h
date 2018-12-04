#ifndef CONNECTSTAT_H
#define CONNECTSTAT_H

#include "graph.h"
#include "stat.h"

namespace snu {

	void connect_stat(DSGraph *graph, DSResult *result);
	void connect_stat(USGraph *graph, USResult *result);
}

#endif // CONNECTSTAT_H