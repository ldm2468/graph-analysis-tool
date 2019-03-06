#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "stat.h"
#include "plot.h"


namespace snu {

    class Graph;    // graph having common aspects
    class DSGraph;  // directed simple graph
    class USGraph;  // undirected simple graph

    typedef class Graph Graph;
    typedef class DSGraph DSGraph;
    typedef class USGraph USGraph;

    class Graph {
    public:
        typedef int Vid;             // vertex id
        typedef int Eid;             // edge id
        typedef std::string Vlabel;  // vertex label
        typedef std::string Elabel;  // edge label
        typedef int Weight;          // integer type weight, other types of weight can be added

        class Vertex;
        class Edge;
        class Label_of_Vertices;
        class Label_of_Edges;

        class Vertex {
        public:
            Vid id;
            std::list<Label_of_Vertices*> labels;
            std::list<Edge*> edges;
            unsigned int indegree;
            void *temp;
        };

        class Edge {
        public:
            Eid id;
            std::list<Label_of_Edges*> labels;
            Vertex *from;  // In case of undirected graphs, there is no difference between from and to.
            Vertex *to;
            Weight wgt;
        };

        class Label_of_Vertices {
        public:
            Vlabel label;
            std::list<Vertex*> vertices;
        };

        class Label_of_Edges {
        public:
            Elabel label;
            std::list<Edge*> edges;
        };
    
        std::unordered_map<Vid, Vertex*> id_to_vertex;
        std::unordered_map<Eid, Edge*> id_to_edge;

        std::unordered_map<Vlabel, Label_of_Vertices*> vlabel_to_class;
        std::unordered_map<Elabel, Label_of_Edges*> elabel_to_class;

        struct pair_hash {
            inline unsigned long long operator()(const std::pair<Vid, Vid> &v) const {
                return ((unsigned long long)v.first << 32) + v.second;
            }
        };

        std::unordered_set<std::pair<Vid, Vid>, pair_hash> is_connected;

        unsigned int negative_edge_num = 0;
        char visit = 0;

        Graph();   // prevent from creating Graph class and allow creating graph in subclass
        ~Graph();  // destructor

        // add vertex
        // if vertex is created normally, then return 0
        // if error occurs, then return 1
        int add_vertex(Vid id, unsigned int num, Vlabel lbl[]);  // array version
        int add_vertex(Vid id, std::vector <Vlabel> *lbl);       // vector version

        // directed form of add_edge
        // if edge is created normally, then return 0
        // if error occurs, then return 1
        int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt);  // array version

        friend unsigned long long BFS(Graph::Vertex *start);
    };

    // directed simple graph
    class DSGraph: public Graph {
    public:
        int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt);  // array version
        int add_edge(Eid id, std::vector <Elabel> *lbl, Vid from, Vid to, Weight wgt);       // vector version

        friend void basic_stat(DSGraph *graph, DSResult *result);
        friend void connect_stat(DSGraph *graph, DSResult *result);
        friend void make_plot(DSGraph *graph, Plot *plot);
        
        friend DSGraph *parse_snu_DSGraph(std::string file_path);
        friend DSGraph *parse_net_DSGraph(std::string file_path);
        friend DSGraph *parse_snap_DSGraph(std::string file_path);
    };

    // undirected simple graph
    class USGraph: public Graph {
    public:
        int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt);  // array version
        int add_edge(Eid id, std::vector <Elabel> *lbl, Vid from, Vid to, Weight wgt);       // vector version

        friend void basic_stat(USGraph *graph, USResult *result);
        friend void connect_stat(USGraph *graph, USResult *result);
        friend void count_stat(USGraph *graph, USResult *result);
        friend void make_plot(USGraph *graph, Plot *plot);

        friend USGraph *parse_snu_USGraph(std::string file_path);
        friend USGraph *parse_snap_USGraph(std::string file_path);
    };
}

#endif // GRAPH_H

