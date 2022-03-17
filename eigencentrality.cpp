#include "eigencentrality.h"
#include "matrix.h"

#include <cmath>

namespace snu {
    static bool matrixBasedPageRank(Graph &graph, std::vector<double> &prob) {
        int n = (int) graph.id_to_vertex.size();
        auto mat = new Matrix(n, n);
        std::vector<double> mul;
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
        double damper = 1. - PAGERANK_DAMPING_FACTOR;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            mat->mul(prob, mul);
            for (int i = 0; i < n; i++) {
                double next = damper + PAGERANK_DAMPING_FACTOR * mul[i];
                if (std::abs(next - prob[i]) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[i] = next;
            }
        }

        delete mat;
        return !not_finished;
    }

    static bool matrixBasedEigenCentrality(Graph &graph, std::vector<double> &prob) {
        int n = (int) graph.id_to_vertex.size();
        auto mat = new Matrix(n, n);
        std::vector<double> mul;
        prob.resize(n);

        for (auto& pair: graph.id_to_vertex) {
            auto g = pair.second;
            prob[g->id] = 1. / (double) n;

            if (!g->edges.empty()) {
                for (auto& edge: g->edges) {
                    auto to = edge->to == g ? edge->from : edge->to;
                    mat->at((int) to->id, (int) g->id) = 1;
                }
            }
        }

        bool not_finished = true;
        int iterations = 0;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            mat->mul(prob, mul);
            double sum_sq = 0;
            for (int i = 0; i < n; i++) {
                sum_sq += mul[i] * mul[i];
            }
            sum_sq = std::sqrt(sum_sq);
            for (int i = 0; i < n; i++) {
                double next = mul[i] / sum_sq;
                if (std::abs(prob[i] - next) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[i] = next;
            }
        }
        delete mat;
        if (not_finished) {
            return false;
        }

        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += prob[i];
        }
        for (int i = 0; i < n; i++) {
            prob[i] *= n / sum;
        }

        return true;
    }

    void eigenCentrality(Graph &graph, StatResult &result) {
        int n = (int) graph.id_to_vertex.size();
        std::vector<double> prob;
        if (matrixBasedEigenCentrality(graph, prob)) {
            result.eigencentrality_converged = true;
            result.max_eigencentrality = 0;
            for (int i = 0; i < n; i++) {
                if (prob[i] > result.max_eigencentrality) {
                    result.max_eigencentrality = prob[i];
                    result.max_eigencentrality_id = i;
                }
            }
        }
        if (matrixBasedPageRank(graph, prob)) {
            result.pagerank_converged = true;
            result.max_pagerank = 0;
            for (int i = 0; i < n; i++) {
                if (prob[i] > result.max_pagerank) {
                    result.max_pagerank = prob[i];
                    result.max_pagerank_id = i;
                }
            }
        }

        result.eigencentralitystat = true;
    }
}
