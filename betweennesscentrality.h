#ifndef BETWEENNESSCENTRALITY_H
#define BETWEENNESSCENTRALITY_H

#include "graph.h"
#include "stat.h"
#include <set>

#define MAX_BETWEENNESS_SAMPLE_SZ 100

namespace snu
{
  class BetweennessCentrality : public CommonStat
  {
  public:
    virtual std::string statName() override;

  protected:
    virtual bool calculateStat(Graph &graph) override;
    virtual void writeToHTMLStat(FILE *fp, bool directed) override;
    virtual void writeToFileStat(std::string graph_name, bool directed) override;

  private:
    void augmented_dijkstra(const Graph &graph, Graph::Vertex *start,
                            std::unordered_map<Graph::Vid, std::set<Graph::Vid>> &out_predecessors,
                            std::unordered_map<Graph::Vid, int64_t> &out_pathcount,
                            std::unordered_map<Graph::Vid, int64_t> &dist,
                            bool reversed);
    bool applyPartialValue(const Graph &graph, Graph::Vertex *A,
                           std::unordered_map<Graph::Vid, float> &betweennessValue,
                           bool reversed);

    std::unordered_map<Graph::Vid, float> betweennessValue;
    double max_betweenness_centrality;       // maximum betweenness centrality value
    long long max_betweenness_centrality_id; // id of max betweenness centrality vertex
  };
}

#endif // BETWEENNESSCENTRALITY_H
