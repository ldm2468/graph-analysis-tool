#ifndef EIGENCENTRALITY_H
#define EIGENCENTRALITY_H

#include "graph.h"
#include "stat.h"

#define PAGERANK_DAMPING_FACTOR 0.85
#define CONVERGENCE_TEST 1E-5
#define MAX_ITERATIONS 100
#define KATZ_ITERATIONS 100

namespace snu {
class EigenCentrality : public CommonStat {
   public:
    virtual std::string statName() override;

   protected:
    virtual bool calculateStat(Graph &graph) override;
    virtual void writeToHTMLStat(FILE *fp, bool directed) override;

   private:
    void normalizeProb(int n, std::unordered_map<Graph::Vid, double> &prob);
    bool calcPageRank(Graph &graph, std::unordered_map<Graph::Vid, double> &prob);
    double calcEigenCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob);
    void calcKatzCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob, double eigenvalue);

    bool pagerank_converged = false;         // whether pagerank converged
    double max_pagerank;                     // maximum pagerank value
    long long max_pagerank_id;               // id of max pagerank value vertex
    bool eigencentrality_converged = false;  // whether eigencentrality converged
    double max_eigencentrality;              // maximum eigencentrality value
    long long max_eigencentrality_id;        // id of max eigencentrality vertex
    bool katz_centrality_computed = false;   // whether katz centrality was computed
    double max_katz_centrality;              // maximum katz centrality value
    long long max_katz_centrality_id;        // id of max katz centrality vertex
    double max_eigenvalue;                   // maximum eigenvalue calculated with eigencentrality
};
}  // namespace snu

#endif  // EIGENCENTRALITY_H
