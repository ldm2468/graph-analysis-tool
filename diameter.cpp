#include "diameter.h"

#include <queue>

namespace snu {
    inline unsigned long long max(unsigned long long x, unsigned long long y)
    {
        return (x > y) ? x : y;
    }

    // Given a node, returns a pair of the farthest node and its distance form the node.
    std::pair<Graph::Vertex*, unsigned long long> farthest(USGraph& graph, Graph::Vertex* root)
    {
        const unsigned long long INF = 0x7fffffffffffffff;

        // `temp` stores distance from the root node.
        // Initialize those distances to inf.
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            vertex->temp = new unsigned long long(INF);
        }

        std::queue<Graph::Vertex*> vertex_queue;

        *static_cast<unsigned long long*>(root->temp) = 0;
        vertex_queue.push(root);

        // Perform BFS and calculate distances to each node from the root node.
        while (!vertex_queue.empty()) {
            Graph::Vertex* curr = vertex_queue.front(); vertex_queue.pop();
            unsigned long long curr_dist = *static_cast<unsigned long long*>(curr->temp);

            for (auto edge: curr->edges) {
                Graph::Vertex* next = (edge->to == curr) ? edge->from : edge->to;
                unsigned long long next_dist = *static_cast<unsigned long long*>(next->temp);

                if (curr_dist + 1 < next_dist) {
                    *static_cast<unsigned long long*>(next->temp) = curr_dist + 1;
                    vertex_queue.push(next);
                }
            }
        }

        // Find the farthest node and its distance from the root node.
        Graph::Vertex* farthest_vertex = nullptr;
        unsigned long long farthest_dist = 0;
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            unsigned long long dist = *static_cast<unsigned long long*>(vertex->temp);
            if (dist != INF && farthest_dist < dist) {
                farthest_dist = dist;
                farthest_vertex = vertex;
            }            
        }

        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            delete static_cast<unsigned long long*>(vertex->temp);
        }

        return std::make_pair(farthest_vertex, farthest_dist);
    }

    // Given a graph, returns the exact diameter of the graph.
    unsigned long long diameter(USGraph& graph)
    {
        unsigned long long max_dist = 0;
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;

            // `farthest` returns a pair of the farthest node and its distance from the vertex.
            unsigned long long dist = farthest(graph, vertex).second;
            max_dist = max(dist, max_dist);
        }

        return max_dist;
    }

    // Given a graph, returns an approximate diameter of the graph.
    unsigned long long approximate_diameter(USGraph& graph)
    {
        // Begin with an arbitray node(=root).
        Graph::Vertex* root = graph.id_to_vertex.begin()->second;
        
        // Find the farthest node from the root.
        Graph::Vertex* node = farthest(graph, root).first;

        // Return the distance between the node and the farthest node from the node.
        return farthest(graph, node).second;
    }
}

