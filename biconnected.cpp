#include "biconnected.h"
#include <stack>

namespace snu {
    typedef struct VertexMetadata {
        bool visited = false;
        bool is_articulation_point = false;
        long long depth = -1; // the depth in the dfs
        long long low_point = -1; // depth of topmost ancestor reachable
        long long child_count = 0; // number of children in dfs tree
        Graph::Vertex *parent = nullptr; // the parent in the dfs tree
    } VertexMetadata;

    static VertexMetadata *getMetadata(Graph::Vertex *v) {
        return (VertexMetadata *) v->temp;
    }

    void biconnectedComponents(Graph& graph, StatResult& result) {
        for (auto& pair: graph.id_to_vertex) {
            pair.second->temp = new VertexMetadata();
        }

        result.num_biconnected_components = 0;

        std::stack<Graph::Vertex *> dfs_stack;

        for (auto& pair: graph.id_to_vertex) {
            Graph::Vertex *root = pair.second;
            VertexMetadata *root_meta = getMetadata(root);
            if (!root_meta->visited) {
                root_meta->depth = 0;
                dfs_stack.push(root);
                while (!dfs_stack.empty()) {
                    bool escape = false;
                    Graph::Vertex *v = dfs_stack.top();
                    VertexMetadata *meta = getMetadata(v);
                    if (!meta->visited) {
                        meta->low_point = meta->depth;
                        meta->visited = true;
                    }
                    for (auto& e: v->edges) {
                        Graph::Vertex *to = e->to == v ? e->from : e->to;
                        VertexMetadata *to_meta = getMetadata(to);

                        if (!to_meta->visited) { // this is a child!
                            meta->child_count++;
                            to_meta->parent = v;
                            to_meta->depth = meta->depth + 1;
                            dfs_stack.push(to);
                            escape = true;
                            break;
                        } else if (to != meta->parent) {
                            if (meta->low_point > to_meta->depth) { // this is a back edge!
                                meta->low_point = to_meta->depth;
                            }
                        }
                    }
                    if (escape) {
                        continue;
                    }
                    if (v == root) {
                        if (meta->child_count > 1) {
                            // if dfs tree root has multiple children, it must be an articulation point!
                            meta->is_articulation_point = true;
                        }
                        result.num_biconnected_components += meta->child_count;
                        break; // finished processing root, stack should be empty
                    }
                    if (meta->depth > 1) { // if parent isn't root...
                        if (meta->low_point == getMetadata(meta->parent)->depth || meta->low_point == meta->depth) {
                            getMetadata(meta->parent)->is_articulation_point = true;
                            result.num_biconnected_components++;
                        }
                    }
                    if (getMetadata(meta->parent)->low_point > meta->low_point) {
                        getMetadata(meta->parent)->low_point = meta->low_point;
                    }
                    dfs_stack.pop();
                }
            }
        }

        result.num_articulation_points = 0;
        for (auto& pair: graph.id_to_vertex) {
            if (getMetadata(pair.second)->is_articulation_point) {
                result.num_articulation_points++;
            }
        }
        result.biconnectedstat = true;

        for (auto& pair: graph.id_to_vertex) {
            delete getMetadata(pair.second);
        }
    }
}

