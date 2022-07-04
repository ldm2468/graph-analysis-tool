#include "eigencentrality.h"
#include <cmath>

namespace snu
{
  std::string EigenCentrality::statName()
  {
    return "EigenCentrality";
  }

  bool EigenCentrality::calculateStat(Graph &graph)
  {
    int n = (int)graph.id_to_vertex.size();
    std::unordered_map<Graph::Vid, double> prob;
    if ((max_eigenvalue = calcEigenCentrality(graph, prob)) >= 1E-12)
    {
      normalizeProb(n, prob);
      eigencentrality_converged = true;
      max_eigencentrality = 0;
      for (auto &pair : graph.id_to_vertex)
      {
        if (prob[pair.first] > max_eigencentrality)
        {
          max_eigencentrality = prob[pair.first];
          max_eigencentrality_id = pair.first;
        }
      }
    }

    if (calcPageRank(graph, prob))
    {
      normalizeProb(n, prob);
      pagerank_converged = true;
      max_pagerank = 0;
      for (auto &pair : graph.id_to_vertex)
      {
        if (prob[pair.first] > max_pagerank)
        {
          max_pagerank = prob[pair.first];
          max_pagerank_id = pair.first;
        }
      }
    }

    calcKatzCentrality(graph, prob, max_eigenvalue);
    normalizeProb(n, prob);
    katz_centrality_computed = true;
    max_katz_centrality = 0;
    for (auto &pair : graph.id_to_vertex)
    {
      if (prob[pair.first] > max_katz_centrality)
      {
        max_katz_centrality = prob[pair.first];
        max_katz_centrality_id = pair.first;
      }
    }

    return true;
  }

  void EigenCentrality::writeToHTMLStat(FILE *fp, bool directed)
  {
    fprintf(fp, "\
                <h2>\
                    Eigenvector Centrality Statistics\
                </h2>\
                <h3>\
                <p> max eigenvalue = %lf</p>",
            max_eigenvalue);
    if (eigencentrality_converged)
    {
      fprintf(fp, "<p> max eigenvector centrality value = %lf at ID = %lld </p>",
              max_eigencentrality, max_eigencentrality_id);
    }
    else
    {
      fprintf(fp, "<p> eigenvector centrality failed to converge. </p>");
    }
    if (pagerank_converged)
    {
      fprintf(fp, "<p> max PageRank value = %lf at ID = %lld </p>",
              max_pagerank, max_pagerank_id);
    }
    else
    {
      fprintf(fp, "<p> PageRank failed to converge. </p>");
    }
    if (katz_centrality_computed)
    {
      fprintf(fp, "<p> max Katz centrality value = %lf at ID = %lld </p>",
              max_katz_centrality, max_katz_centrality_id);
    }
    fprintf(fp, "</h3>");
  }

  void EigenCentrality::normalizeProb(int n, std::unordered_map<Graph::Vid, double> &prob)
  {
    double sum = 0;
    for (auto &pair : prob)
    {
      sum += pair.second;
    }
    for (auto &pair : prob)
    {
      pair.second *= n / sum;
    }
  }

  bool EigenCentrality::calcPageRank(Graph &graph, std::unordered_map<Graph::Vid, double> &prob)
  {
    std::unordered_map<Graph::Eid, double> mul; // matrix multiplication result

    for (auto &pair : graph.id_to_vertex)
    {
      prob[pair.second->id] = 1;
    }

    bool not_finished = true;
    int iterations = 0;
    double damper = 1. - PAGERANK_DAMPING_FACTOR;
    while (not_finished && iterations < MAX_ITERATIONS)
    {
      iterations++;
      not_finished = false;
      for (auto &pair : graph.id_to_vertex)
      {
        mul[pair.first] = 0; // prepare matrix multiplication result
      }
      for (auto &pair : graph.id_to_vertex)
      {
        auto g = pair.second;
        if (!g->edges.empty())
        {
          double w = 1. / (double)g->edges.size();
          for (auto &edge : g->edges)
          {
            auto to = edge->to == g ? edge->from : edge->to;
            mul[to->id] += w * prob[g->id];
          }
        }
      }
      for (auto &pair : graph.id_to_vertex)
      {
        double next = damper + PAGERANK_DAMPING_FACTOR * mul[pair.first];
        if (std::abs(next - prob[pair.first]) > CONVERGENCE_TEST)
        {
          not_finished = true;
        }
        prob[pair.first] = next;
      }
    }

    return !not_finished;
  }

  double EigenCentrality::calcEigenCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob)
  {
    std::unordered_map<Graph::Vid, double> mul;
    double eigenvalue;

    for (auto &pair : graph.id_to_vertex)
    {
      prob[pair.second->id] = 1;
    }

    bool not_finished = true;
    int iterations = 0;
    while (not_finished && iterations < MAX_ITERATIONS)
    {
      iterations++;
      not_finished = false;
      for (auto &pair : graph.id_to_vertex)
      {
        mul[pair.first] = 0; // prepare matrix multiplication result
      }
      for (auto &pair : graph.id_to_vertex)
      {
        auto g = pair.second;
        if (!g->edges.empty())
        {
          for (auto &edge : g->edges)
          {
            auto to = edge->to == g ? edge->from : edge->to;
            mul[to->id] += prob[g->id];
          }
        }
      }
      eigenvalue = 0;
      for (auto &pair : graph.id_to_vertex)
      {
        double m = mul[pair.first];
        eigenvalue += m * m;
      }
      eigenvalue = std::sqrt(eigenvalue);
      if (eigenvalue <= 1E-12)
      {
        eigenvalue = 0;
        break;
      }
      for (auto &pair : graph.id_to_vertex)
      {
        double next = mul[pair.first] / eigenvalue;
        if (std::abs(prob[pair.first] - next) > CONVERGENCE_TEST)
        {
          not_finished = true;
        }
        prob[pair.first] = next;
      }
    }

    return eigenvalue;
  }

  void EigenCentrality::calcKatzCentrality(Graph &graph, std::unordered_map<Graph::Vid, double> &prob, double eigenvalue)
  {
    std::unordered_map<Graph::Vid, double> pow, tmp;

    double att = eigenvalue <= 0 ? 0.8 : std::min(1. / eigenvalue, 1.) * 0.8;

    for (auto &pair : graph.id_to_vertex)
    {
      pow[pair.first] = 1;
    }

    for (int it = 0; it < KATZ_ITERATIONS; it++)
    {
      for (auto &pair : graph.id_to_vertex)
      {
        tmp[pair.first] = 0;
      }
      for (auto &pair : graph.id_to_vertex)
      {
        auto g = pair.second;
        if (!g->edges.empty())
        {
          for (auto &edge : g->edges)
          {
            auto to = edge->to == g ? edge->from : edge->to;
            tmp[to->id] += pow[g->id] * att;
          }
        }
      }
      pow = tmp;

      for (auto &pair : graph.id_to_vertex)
      {
        prob[pair.first] += pow[pair.first];
      }
    }
  }
}
