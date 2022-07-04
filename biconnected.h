#ifndef BICONNECTED_H
#define BICONNECTED_H

#include "graph.h"
#include "stat.h"

namespace snu
{
  class BiconnectedComponents : public UndirectedStat
  {
  public:
    virtual std::string statName() override;

  protected:
    virtual bool calculateUndirectedStat(USGraph &graph) override;
    virtual void writeToHTMLStat(FILE *fp, bool directed) override;

  private:
    void countBcc(USGraph &graph);

    long long num_arp;      // number of articulation points
    long long num_bcc;      // number of biconnected components
    long long max_conn_bcc; // maximum number of bcc's connected to a single arp
    long long size_lbcc;    // largest size of biconnected components
  };
}

#endif // BICONNECTED_H
