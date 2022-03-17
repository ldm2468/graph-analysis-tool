#ifndef EIGENCENTRALITY_H
#define EIGENCENTRALITY_H

#include "graph.h"
#include "stat.h"

#define DAMPING_FACTOR 0.85
#define CONVERGENCE_TEST 1E-6

namespace snu {
    void pageRank(Graph &graph, StatResult &result);
}

#endif //EIGENCENTRALITY_H
