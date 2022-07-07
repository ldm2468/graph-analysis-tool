#ifndef CLOSENESSCENTRALITY_H
#define CLOSENESSCENTRALITY_H

#include <map>

#include "graph.h"
#include "stat.h"

#define MAX_CLOSENESS_SAMPLE_SZ 100

namespace snu {
class ClosenessCentrality : public CommonStat {
   public:
    virtual std::string statName() override;

   protected:
    virtual bool calculateStat(Graph &graph, bool verify) override;
    virtual void writeToHTMLStat(FILE *fp, bool directed) override;
    virtual bool writeToFileStat(std::string graph_name, bool directed) override;

   private:
    std::map<Graph::Vid, int64_t> dijkstra(const Graph &graph, Graph::Vertex *start, bool inbound);
    bool calculate(Graph &graph, bool inbound, std::map<Graph::Vid, double> &cc, double &max, long long &max_id);
    void writeMap(std::string fname, std::map<Graph::Vid, double> map);

    double max_closeness_centrality;
    double max_inbound_closeness_centrality;
    long long max_closeness_centrality_id;  // id of max closeness centrality vertex
    long long max_inbound_closeness_centrality_id;
    std::map<Graph::Vid, double> closeness_centrality;
    std::map<Graph::Vid, double> inbound_closeness_centrality;
};
}  // namespace snu

#endif  // CLOSENESSCENTRALITY_H
