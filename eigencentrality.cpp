#include "eigencentrality.h"

namespace snu {
    typedef struct VertexMetadata {
        double prob;
    } VertexMetadata;

    static VertexMetadata *getMetadata(Graph::Vertex *v) {
        return (VertexMetadata *) v->temp;
    }

    void pageRank(Graph &graph, StatResult &result) {
        for (auto& pair: graph.id_to_vertex) {
            pair.second->temp = new VertexMetadata();
        }

        for (auto& pair: graph.id_to_vertex) {
            delete getMetadata(pair.second);
        }
    }
}
