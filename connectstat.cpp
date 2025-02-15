#include "connectstat.h"

#include <queue>
#include <stack>
#include <vector>

namespace snu {

typedef struct VertexInfo {
    std::vector<Graph::Edge *> reverse_edges;  // to -> from
    bool visit;                                // default: false
} VertexInfo;

// SCC
class Kosaraju {
   public:
    static void first(Graph::Vertex *start, std::stack<Graph::Vertex *> *s) {
        std::stack<Graph::Vertex *> s1;
        std::stack<std::list<Graph::Edge *>::iterator> s2;
        s1.push(start);
        s2.push(start->edges.begin());
        s2.push(start->edges.end());

        VertexInfo *start_info = (VertexInfo *)start->temp;
        start_info->visit = true;

        while (!s1.empty()) {
            auto end = s2.top();
            s2.pop();
            auto it = s2.top();
            s2.pop();

            for (; it != end; it++) {
                Graph::Vertex *next = (*it)->to;
                VertexInfo *next_info = (VertexInfo *)next->temp;

                if (!next_info->visit) {
                    next_info->visit = true;
                    auto it2 = it;
                    s2.push(++it2);
                    s2.push(end);
                    s1.push(next);
                    s2.push(next->edges.begin());
                    s2.push(next->edges.end());
                    break;
                }
            }

            if (it == end) {
                s->push(s1.top());
                s1.pop();
            }
        }
    }

    static long long second(Graph::Vertex *start) {
        long long cnt = 0;
        VertexInfo *now_info, *next_info;
        std::queue<Graph::Vertex *> q;

        now_info = (VertexInfo *)start->temp;
        now_info->visit = false;
        q.push(start);

        while (!q.empty()) {
            Graph::Vertex *now = q.front();
            q.pop();
            cnt++;
            now_info = (VertexInfo *)now->temp;

            // reverse edges
            for (auto it = now_info->reverse_edges.begin(); it != now_info->reverse_edges.end(); it++) {
                Graph::Vertex *next = (*it)->from;
                next_info = (VertexInfo *)next->temp;

                if (next_info->visit) {
                    next_info->visit = false;
                    q.push(next);
                }
            }
        }

        return cnt;
    }
};

// WCC
class WCC {
   public:
    static long long bfs(Graph::Vertex *start) {
        long long cnt = 0;
        VertexInfo *now_info, *next_info;
        std::queue<Graph::Vertex *> q;

        now_info = (VertexInfo *)start->temp;
        now_info->visit = true;
        q.push(start);

        while (!q.empty()) {
            Graph::Vertex *now = q.front();
            q.pop();
            cnt++;
            now_info = (VertexInfo *)now->temp;

            // edges
            for (auto it = now->edges.begin(); it != now->edges.end(); it++) {
                Graph::Vertex *next = (*it)->to;
                next_info = (VertexInfo *)next->temp;

                if (!next_info->visit) {
                    next_info->visit = true;
                    q.push(next);
                }
            }

            // reverse edges
            for (auto it = now_info->reverse_edges.begin(); it != now_info->reverse_edges.end(); it++) {
                Graph::Vertex *next = (*it)->from;
                next_info = (VertexInfo *)next->temp;

                if (!next_info->visit) {
                    next_info->visit = true;
                    q.push(next);
                }
            }
        }

        return cnt;
    }
};

// For Undirected Simple Graph
typedef struct FirstInfo {
    Graph::Vertex *farthest;
    long long size_cc;
} FirstInfo;

typedef struct USVertexInfo {
    long long dist;
    bool visit;
} USVertexInfo;

class BFS {
   public:
    static FirstInfo first(Graph::Vertex *start) {
        long long cnt = 0;
        Graph::Vertex *now = start;
        USVertexInfo *now_info, *next_info;
        std::queue<Graph::Vertex *> q;

        now_info = (USVertexInfo *)now->temp;
        now_info->visit = true;
        now_info->dist = 0;
        q.push(start);

        while (!q.empty()) {
            now = q.front();
            q.pop();
            cnt++;
            now_info = (USVertexInfo *)now->temp;

            for (auto it = now->edges.begin(); it != now->edges.end(); it++) {
                Graph::Vertex *next = now == (*it)->to ? (*it)->from : (*it)->to;
                next_info = (USVertexInfo *)next->temp;

                if (!next_info->visit) {
                    next_info->visit = true;
                    next_info->dist = now_info->dist + 1;
                    q.push(next);
                }
            }
        }

        return FirstInfo{now, cnt};
    }

    static long long second(Graph::Vertex *start) {
        USVertexInfo *now_info, *next_info;
        std::queue<Graph::Vertex *> q;

        now_info = (USVertexInfo *)start->temp;
        now_info->visit = false;
        now_info->dist = 0;
        q.push(start);

        while (!q.empty()) {
            Graph::Vertex *now = q.front();
            q.pop();
            now_info = (USVertexInfo *)now->temp;

            for (auto it = now->edges.begin(); it != now->edges.end(); it++) {
                Graph::Vertex *next = now == (*it)->to ? (*it)->from : (*it)->to;
                next_info = (USVertexInfo *)next->temp;

                if (next_info->visit) {
                    next_info->visit = false;
                    next_info->dist = now_info->dist + 1;
                    q.push(next);
                }
            }
        }

        return now_info->dist;
    }
};

std::string ConnectStat::statName() {
    return "ConnectStat";
}

bool ConnectStat::calculateStat(Graph &graph, bool verify) {
    DSGraph *dsgraph = dynamic_cast<DSGraph *>(&graph);
    USGraph *usgraph = dynamic_cast<USGraph *>(&graph);

    if (dsgraph)
        return calcDS(*dsgraph);
    else if (usgraph)
        return calcUS(*usgraph);
    return false;
}

void ConnectStat::writeToHTMLStat(FILE *fp, bool directed) {
    if (directed)
        htmlDS(fp);
    else
        htmlUS(fp);
}

void ConnectStat::htmlDS(FILE *fp) {
    fprintf(fp,
            "\
			<h2>\
					Connectivity Statistics\
			</h2>\
			<h3>\
					<p> number of strongly connected components = %lld </p>\
					<p> size of largest strongly connected component = %lld </p>\
					<p> number of weakly connected components = %lld </p>\
					<p> size of largest weakly connected component = %lld </p>\
			</h3>\
		",
            num_scc, size_lscc, num_wcc, size_lwcc);
}

void ConnectStat::htmlUS(FILE *fp) {
    fprintf(fp,
            "\
			<h2>\
					Connectivity Statistics\
			</h2>\
			<h3>\
					<p> number of connected components = %lld </p>\
					<p> size of largest connected component = %lld </p>\
					<p> approximate diameter (largest distance of all shortest path) = %lld </p>\
			</h3>\
		",
            num_cc, size_lcc, diameter);
}

bool ConnectStat::calcDS(DSGraph &graph) {
    // create additional information for BFS and DFS
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++)
        it->second->temp = new VertexInfo();
    for (auto it = graph.id_to_edge.begin(); it != graph.id_to_edge.end(); it++) {
        Graph::Edge *edge = it->second;
        VertexInfo *info = (VertexInfo *)edge->to->temp;
        info->reverse_edges.push_back(edge);
    }

    std::stack<Graph::Vertex *> s;

    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++) {
        VertexInfo *info = (VertexInfo *)it->second->temp;
        if (!info->visit)
            Kosaraju::first(it->second, &s);
    }

    num_scc = 0;
    size_lscc = 0;

    long long hab = 0;

    while (!s.empty()) {
        Graph::Vertex *v = s.top();
        s.pop();
        VertexInfo *info = (VertexInfo *)v->temp;

        if (info->visit) {
            num_scc++;
            long long size_scc = Kosaraju::second(v);
            hab += size_scc;
            size_lscc = std::max(size_lscc, size_scc);
        }
    }

    num_wcc = 0;
    size_lwcc = 0;
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++) {
        VertexInfo *info = (VertexInfo *)it->second->temp;
        if (!info->visit) {
            num_wcc++;
            long long size_wcc = WCC::bfs(it->second);
            size_lwcc = std::max(size_lwcc, size_wcc);
        }
    }

    // delete additional information created before
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++)
        delete (VertexInfo *)it->second->temp;

    return true;
}

bool ConnectStat::calcUS(USGraph &graph) {
    // create additional information for BFS
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++)
        it->second->temp = new USVertexInfo();  // temp as visit

    num_cc = 0;
    size_lcc = 0;
    std::vector<Graph::Vertex *> vertices;
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++) {
        if (!(*(char *)it->second->temp)) {
            num_cc++;
            FirstInfo info = BFS::first(it->second);
            vertices.push_back(info.farthest);
            size_lcc = std::max(size_lcc, info.size_cc);
        }
    }

    // following code computes approximate diameter, which is exact for trees, by conducting BFS twice.
    // Note that 'vertices' contains a farthest vertex of the first BFS for each connected component.
    diameter = 0;
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        long long dist = BFS::second(*it);
        diameter = std::max(diameter, dist);
    }

    // delete additional information created before
    for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++)
        delete (USVertexInfo *)it->second->temp;

    return true;
}
}  // namespace snu
