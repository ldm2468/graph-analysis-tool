#include "eigencentrality.h"
#include "matrix.h"

namespace snu {
    void pageRank(Graph &graph, StatResult &result) {
        int n = (int) graph.id_to_vertex.size();
        auto mat = new Matrix(n, n);
        std::vector<double> prob, mul;
        prob.resize(n);

        for (auto& pair: graph.id_to_vertex) {
            auto g = pair.second;
            prob[g->id] = 1;

            if (!g->edges.empty()) {
                double w = 1. / (double) g->edges.size();
                for (auto& edge: g->edges) {
                    auto to = edge->to == g ? edge->from : edge->to;
                    mat->at((int) to->id, (int) g->id) = w;
                }
            }
        }

        bool not_finished = true;
        int iterations = 0;
        double damper = 1. - DAMPING_FACTOR;
        while (not_finished) {
            iterations++;
            not_finished = false;
            mat->mul(prob, mul);
            for (int i = 0; i < prob.size(); i++) {
                double next = damper + DAMPING_FACTOR * mul[i];
                if ((next > prob[i] ? next - prob[i] : prob[i] - next) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[i] = next;
            }
        }

        result.max_pagerank = 0;
        for (int i = 0; i < n; i++) {
            if (prob[i] > result.max_pagerank) {
                result.max_pagerank = prob[i];
            }
        }

        result.eigencentralitystat = true;
    }
}
