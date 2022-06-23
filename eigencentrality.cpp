#include "eigencentrality.h"
#include <cmath>

namespace snu {
    static void normalizeProb(double n, std::vector<double> &probv) {
        double sum = 0;
        for (double p: probv) {
            sum += p;
        }
        for (double& p: probv) {
            p *= n / sum;
        }
    }

    static bool calcPageRank(Graph &graph, std::vector<double> &probv) {
        std::vector<double> mulv;
        mulv.resize(graph.V);

        std::fill(probv.begin(), probv.end(), 1);

        bool not_finished = true;
        int iterations = 0;
        double damper = 1. - PAGERANK_DAMPING_FACTOR;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            std::fill(mulv.begin(), mulv.end(), 0); // prepare matrix multiplication result
            for (size_t i = 0; i < graph.V; i++) {
                auto g = graph.vertices[i];
                if (!g->edges.empty()) {
                    double w = 1. / (double) g->edges.size();
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        mulv[to->order] += w * probv[g->order];
                    }
                }
            }
            for (size_t i = 0; i < graph.V; i++) {
                double next = damper + PAGERANK_DAMPING_FACTOR * mulv[i];
                if (std::abs(next - probv[i]) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                probv[i] = next;
            }
        }

        return !not_finished;
    }

    static double calcEigenCentrality(Graph &graph, std::vector<double> &probv) {
        std::vector<double> mulv;
        mulv.resize(graph.V);
        double eigenvalue;

        std::fill(probv.begin(), probv.end(), 1);

        bool not_finished = true;
        int iterations = 0;
        while (not_finished && iterations < MAX_ITERATIONS) {
            iterations++;
            not_finished = false;
            std::fill(mulv.begin(), mulv.end(), 0); // prepare matrix multiplication result
            for (size_t i = 0; i < graph.V; i++) {
                auto g = graph.vertices[i];
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        mulv[to->order] += probv[g->order];
                    }
                }
            }
            eigenvalue = 0;
            for (double m: mulv) {
                eigenvalue += m * m;
            }
            eigenvalue = std::sqrt(eigenvalue);
            if (eigenvalue <= 1E-12) {
                eigenvalue = 0;
                break;
            }
            for (size_t i = 0; i < graph.V; i++) {
                double next = mulv[i] / eigenvalue;
                if (std::abs(probv[i] - next) > CONVERGENCE_TEST) {
                    not_finished = true;
                }
                probv[i] = next;
            }
        }

        return eigenvalue;
    }

    static void calcKatzCentrality(Graph &graph, std::vector<double> &probv, double eigenvalue) {
        std::vector<double> powv, tmpv;
        powv.resize(graph.V, 1);
        tmpv.resize(graph.V);

        double att = eigenvalue <= 0 ? 0.8 : std::min(1. / eigenvalue, 1.) * 0.8;

        for (int it = 0; it < KATZ_ITERATIONS; it++) {
            std::fill(tmpv.begin(), tmpv.end(), 0);
            for (size_t i = 0; i < graph.V; i++) {
                auto g = graph.vertices[i];
                if (!g->edges.empty()) {
                    for (auto& edge: g->edges) {
                        auto to = edge->to == g ? edge->from : edge->to;
                        tmpv[to->order] += powv[g->order] * att;
                    }
                }
            }
            std::swap(powv, tmpv);

            for (size_t i = 0; i < graph.V; i++) {
                probv[i] += powv[i];
            }
        }
    }

    void eigenCentrality(Graph &graph, StatResult &result) {
        std::vector<double> probv;
        probv.resize(graph.V);

        if ((result.max_eigenvalue = calcEigenCentrality(graph, probv)) >= 1E-12) {
            normalizeProb((double) graph.V, probv);
            result.eigencentrality_converged = true;
            result.max_eigencentrality = 0;
            for (size_t i = 0; i < graph.V; i++) {
                if (probv[i] > result.max_eigencentrality) {
                    result.max_eigencentrality = probv[i];
                    result.max_eigencentrality_id = graph.vid_order[i];
                }
            }
        }

        if (calcPageRank(graph, probv)) {
            normalizeProb((double) graph.V, probv);
            result.pagerank_converged = true;
            result.max_pagerank = 0;
            for (size_t i = 0; i < graph.V; i++) {
                if (probv[i] > result.max_pagerank) {
                    result.max_pagerank = probv[i];
                    result.max_pagerank_id = graph.vid_order[i];
                }
            }
        }

        calcKatzCentrality(graph, probv, result.max_eigenvalue);
        normalizeProb((double) graph.V, probv);
        result.katz_centrality_computed = true;
        result.max_katz_centrality = 0;
        for (size_t i = 0; i < graph.V; i++) {
            if (probv[i] > result.max_katz_centrality) {
                result.max_katz_centrality = probv[i];
                result.max_katz_centrality_id = graph.vid_order[i];
            }
        }

        result.eigencentralitystat = true;
    }
}
