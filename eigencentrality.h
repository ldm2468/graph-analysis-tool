#ifndef EIGENCENTRALITY_H
#define EIGENCENTRALITY_H

#include "graph.h"
#include "stat.h"

#define PAGERANK_DAMPING_FACTOR 0.85
#define CONVERGENCE_TEST 1E-6
#define MAX_ITERATIONS 1000

namespace snu {
    void eigenCentrality(Graph &graph, StatResult &result);
}

#endif //EIGENCENTRALITY_H
