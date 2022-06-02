#ifndef CLOSENESSCENTRALITY_H
#define CLOSENESSCENTRALITY_H

#include "graph.h"
#include "stat.h"

#define MAX_CLOSENESS_SAMPLE_SZ 100

namespace snu {
    bool closenessCentrality(const Graph &graph, StatResult &result, bool file_output, std::string graph_name);
}

#endif //CLOSENESSCENTRALITY_H
