#include "eigencentrality.h"
#include <cmath>

namespace snu {
    static void normalizeProb(int n, std::vector<double> &prob) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += prob[i];
        }
        for (int i = 0; i < n; i++) {
            prob[i] *= n / sum;
        }
    }

    static bool calcPageRank(Graph &graph, std::vector<double> &prob) {
        int n = (int) graph.id_to_vertex.size();
        std::vector<double> mul;
        prob.resize(n);
        mul.resize(n);

        for (auto& pair: graph.id_to_vertex) {
            prob[pair.second->id] = 1;
        }

        bool not_finished = true;
        int iterations = 0;
        double damper = 1. - PAGERANK_DAMPING_FACTOR;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            std::fill(mul.begin(), mul.end(), 0);
            for (auto& pair: graph.id_to_vertex) {
                auto g = pair.second;
                if (!g->edges.empty()) {
                    double w = 1. / (double) g->edges.size();
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        mul[to->id] += w * prob[g->id];
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                double next = damper + PAGERANK_DAMPING_FACTOR * mul[i];
                if (std::abs(next - prob[i]) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[i] = next;
            }
        }

        return !not_finished;
    }

    static bool calcEigenCentrality(Graph &graph, std::vector<double> &prob) {
        int n = (int) graph.id_to_vertex.size();
        std::vector<double> mul;
        prob.resize(n);
        mul.resize(n);

        for (int i = 0; i < n; i++) {
            prob[i] = 1;
        }

        bool not_finished = true;
        int iterations = 0;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            std::fill(mul.begin(), mul.end(), 0);
            for (auto& pair: graph.id_to_vertex) {
                auto g = pair.second;
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        mul[to->id] += prob[g->id];
                    }
                }
            }
            double sum_sq = 0;
            for (int i = 0; i < n; i++) {
                sum_sq += mul[i] * mul[i];
            }
            sum_sq = std::sqrt(sum_sq);
            if (sum_sq == 0) {
                not_finished = true;
                break;
            }
            for (int i = 0; i < n; i++) {
                double next = mul[i] / sum_sq;
                if (std::abs(prob[i] - next) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[i] = next;
            }
        }
        if (not_finished) {
            return false;
        }

        return true;
    }

    static void calcKatzCentrality(Graph &graph, std::vector<double> &prob) {
        int n = (int) graph.id_to_vertex.size();
        std::vector<double> pow, tmp;
        prob.resize(n);
        pow.resize(n);
        tmp.resize(n);

        for (auto& pair: graph.id_to_vertex) {
            auto g = pair.second;
            pow[g->id] = 1;
        }

        for (int it = 0; it < KATZ_ITERATIONS; it++) {
            std::fill(tmp.begin(), tmp.end(), 0);
            for (auto& pair: graph.id_to_vertex) {
                auto g = pair.second;
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        tmp[to->id] += pow[g->id] * KATZ_ATTENUATION_FACTOR;
                    }
                }
            }
            pow = tmp;

            for (int i = 0; i < n; i++) {
                prob[i] += pow[i];
            }
        }
    }

    void eigenCentrality(Graph &graph, StatResult &result) {
        int n = (int) graph.id_to_vertex.size();
        std::vector<double> prob;
        if (calcEigenCentrality(graph, prob)) {
            normalizeProb(n, prob);
            result.eigencentrality_converged = true;
            result.max_eigencentrality = 0;
            for (int i = 0; i < n; i++) {
                if (prob[i] > result.max_eigencentrality) {
                    result.max_eigencentrality = prob[i];
                    result.max_eigencentrality_id = i;
                }
            }
        }

        if (calcPageRank(graph, prob)) {
            normalizeProb(n, prob);
            result.pagerank_converged = true;
            result.max_pagerank = 0;
            for (int i = 0; i < n; i++) {
                if (prob[i] > result.max_pagerank) {
                    result.max_pagerank = prob[i];
                    result.max_pagerank_id = i;
                }
            }
        }

        calcKatzCentrality(graph, prob);
        normalizeProb(n, prob);
        result.katz_centrality_computed = true;
        result.max_katz_centrality = 0;
        for (int i = 0; i < n; i++) {
            if (prob[i] > result.max_katz_centrality) {
                result.max_katz_centrality = prob[i];
                result.max_katz_centrality_id = i;
            }
        }

        result.eigencentralitystat = true;
    }
}
