#include "eigencentrality.h"
#include <cmath>

namespace snu {
    static void normalizeProb(int n, std::unordered_map<Graph::Vid, double> &prob) {
        double sum = 0;
        for (auto& pair: prob) {
            sum += pair.second;
        }
        for (auto& pair: prob) {
            pair.second *= n / sum;
        }
    }

    static bool calcPageRank(Graph &graph, std::unordered_map<Graph::Vid, double> &prob) {
        std::unordered_map<Graph::Eid, double> mul; // matrix multiplication result

        for (auto& pair: graph.id_to_vertex) {
            prob[pair.second->id] = 1;
        }

        bool not_finished = true;
        int iterations = 0;
        double damper = 1. - PAGERANK_DAMPING_FACTOR;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            for (auto& pair: graph.id_to_vertex) {
                mul[pair.first] = 0; // prepare matrix multiplication result
            }
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
            for (auto& pair: graph.id_to_vertex) {
                double next = damper + PAGERANK_DAMPING_FACTOR * mul[pair.first];
                if (std::abs(next - prob[pair.first]) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[pair.first] = next;
            }
        }

        return !not_finished;
    }

    static double calcEigenCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob) {
        std::unordered_map<Graph::Vid, double> mul;
        double eigenvalue;

        for (auto& pair: graph.id_to_vertex) {
            prob[pair.second->id] = 1;
        }

        bool not_finished = true;
        int iterations = 0;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            for (auto& pair: graph.id_to_vertex) {
                mul[pair.first] = 0; // prepare matrix multiplication result
            }
            for (auto& pair: graph.id_to_vertex) {
                auto g = pair.second;
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        mul[to->id] += prob[g->id];
                    }
                }
            }
            eigenvalue = 0;
            for (auto& pair: graph.id_to_vertex) {
                double m = mul[pair.first];
                eigenvalue += m * m;
            }
            eigenvalue = std::sqrt(eigenvalue);
            if (eigenvalue <= 1E-12) {
                eigenvalue = 0;
                break;
            }
            for (auto& pair: graph.id_to_vertex) {
                double next = mul[pair.first] / eigenvalue;
                if (std::abs(prob[pair.first] - next) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                prob[pair.first] = next;
            }
        }

        return eigenvalue;
    }

    static void calcKatzCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob, double eigenvalue) {
        std::unordered_map<Graph::Vid, double> pow, tmp;

        double att = eigenvalue <= 0 ? 0.8 : std::min(1. / eigenvalue, 1.) * 0.8;

        for (auto& pair: graph.id_to_vertex) {
            pow[pair.first] = 1;
        }

        for (int it = 0; it < KATZ_ITERATIONS; it++) {
            for (auto& pair: graph.id_to_vertex) {
                tmp[pair.first] = 0;
            }
            for (auto& pair: graph.id_to_vertex) {
                auto g = pair.second;
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        tmp[to->id] += pow[g->id] * att;
                    }
                }
            }
            pow = tmp;

            for (auto& pair: graph.id_to_vertex) {
                prob[pair.first] += pow[pair.first];
            }
        }
    }

    void eigenCentrality(Graph &graph, StatResult &result) {
        int n = (int) graph.id_to_vertex.size();
        std::unordered_map<Graph::Vid, double> prob;
        if ((result.max_eigenvalue = calcEigenCentrality(graph, prob)) >= 1E-12) {
            normalizeProb(n, prob);
            result.eigencentrality_converged = true;
            result.max_eigencentrality = 0;
            for (auto& pair: graph.id_to_vertex) {
                if (prob[pair.first] > result.max_eigencentrality) {
                    result.max_eigencentrality = prob[pair.first];
                    result.max_eigencentrality_id = pair.first;
                }
            }
        }

        if (calcPageRank(graph, prob)) {
            normalizeProb(n, prob);
            result.pagerank_converged = true;
            result.max_pagerank = 0;
            for (auto& pair: graph.id_to_vertex) {
                if (prob[pair.first] > result.max_pagerank) {
                    result.max_pagerank = prob[pair.first];
                    result.max_pagerank_id = pair.first;
                }
            }
        }

        calcKatzCentrality(graph, prob, result.max_eigenvalue);
        normalizeProb(n, prob);
        result.katz_centrality_computed = true;
        result.max_katz_centrality = 0;
        for (auto& pair: graph.id_to_vertex) {
            if (prob[pair.first] > result.max_katz_centrality) {
                result.max_katz_centrality = prob[pair.first];
                result.max_katz_centrality_id = pair.first;
            }
        }

        result.eigencentralitystat = true;
    }
}
