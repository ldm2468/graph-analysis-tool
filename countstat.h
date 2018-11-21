#ifndef COUNTSTAT_H
#define COINTSTAT_H

#include "graph.h"
#include "stat.h"

namespace snu {

	void count_stat(DSGraph *graph, DSResult *result);
	void count_stat(USGraph *graph, USResult *result);
}

#endif // COUNTSTAT_H