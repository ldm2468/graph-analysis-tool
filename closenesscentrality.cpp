#include "closenesscentrality.h"
#include <map>
#include <queue>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <sstream>

namespace snu {
    std::string ClosenessCentrality::statName() {
        return "ClosenessCentrality";
    }

    bool ClosenessCentrality::calculateStat(Graph &graph) {
        const auto& vertices = graph.id_to_vertex;
        int V = vertices.size();
        int sample_sz = std::min(V, MAX_CLOSENESS_SAMPLE_SZ);

        std::vector<std::pair<Graph::Vid, Graph::Vertex*>> samples;
        std::sample(vertices.begin(), vertices.end(), std::back_inserter(samples), 
                    sample_sz, std::mt19937{std::random_device{}()});

        std::map<Graph::Vid, int64_t> dist_sum;
        for (auto vid : samples) {
            auto dist = dijkstra(graph, vid.second);
            //if ((int)dist.size() != V) return false; // disconnected graph

            for (auto p : dist) {
                dist_sum[p.first] += p.second;
            }
        }

        std::map<Graph::Vid, double> inv_dist_sum;

        // Consider nodes that do not connect anywhere to have closeness centrality of 1.0
        // This is to match SNAP's definition of closeness centrality.

        for (auto [vid, vert] : vertices)
            inv_dist_sum[vid] = 1.0; 

        for (auto p : dist_sum)
            inv_dist_sum[p.first] = (p.second != 0) ? (100.0 / p.second) : 1.0;
        double total_inv_sum = 0;
        for (auto p : inv_dist_sum)
            total_inv_sum += p.second;
        if (total_inv_sum == 0.0) return false;

        Graph::Vid centralNodeId = 0;
        double max_closeness_centrality = 0.0;
        for (auto [nodeId, closeness_val] : inv_dist_sum) {
            if (closeness_val > max_closeness_centrality) {
                centralNodeId = nodeId;
                max_closeness_centrality = closeness_val;
            }
        }
        
        max_closeness_centrality = max_closeness_centrality / total_inv_sum;
        max_closeness_centrality_id = centralNodeId;
        return true;
    }

    // calculates single-source shortest-path for all nodes connected to start.
    std::map<Graph::Vid, int64_t> ClosenessCentrality::dijkstra(const Graph & graph, Graph::Vertex* start) {
        std::map<Graph::Vid, int64_t> dist;

        typedef std::pair<int64_t, Graph::Vertex*> elem;
        std::priority_queue<elem, std::vector<elem>, std::greater<elem>> pq;
        pq.emplace(0, start);

        while(!pq.empty()) {
            elem cur = pq.top();
            pq.pop();

            auto cur_dist = cur.first;
            auto V = cur.second;
            if (!dist.count(V->id)) {
                dist[V->id] = cur_dist;
                for (const auto& edge : V->edges) {
                    auto next_dist = cur_dist + edge->weight;
                    auto to = edge->to == V ? edge->from : edge->to;
                    pq.emplace(next_dist, to);
                }
            }
        }
        return dist;
    }


	void ClosenessCentrality::writeToFileStat(std::string graph_name, bool directed) {
        std::string fName = graph_name + "_Closeness.txt";
        std::ofstream fout(fName.data());
        for (auto [nodeId, closeness_val] : closeness_centrality) {
            fout << nodeId << ' ' << closeness_val << '\n';
        }
    }

    void ClosenessCentrality::writeToHTMLStat(FILE* fp, bool directed) {
        fprintf(fp, "\
            <h2>\
                Closeness Centrality Statistics\
            </h2>\
            <h3>\
                <p> max closeness centrality value = %lf at ID = %lld </p>\
            </h3>",
            max_closeness_centrality, max_closeness_centrality_id);
    }
}