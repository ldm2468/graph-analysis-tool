/*
 * Created by baneling100 on 2018-08-02.
 */

#ifndef GRAPH_ANALYSIS_TOOL_GRAPH_H
#define GRAPH_ANALYSIS_TOOL_GRAPH_H

// licensed under GNU General Public License v3.0
#include <list>
#include <hash_set>
#include <hash_map>
#include <string>

class DGraph; //   directed graph
class UGraph; // undirected graph

struct Vertex_Label;
struct Edge_Label;
struct Vertex;
struct Edge;


struct Vertex_Label {
	std::string label;
	std::list <Vertex *> vertices;
};

struct Edge_Label {
	std::string label;
	std::list <Edge *> edges;
};

struct Vertex {
	std::string id;
	std::list <Vertex_Label *> labels;
	std::list <Edge *> edges;
};

struct Edge {
	std::string id;
	std::list <Edge_Label *> labels;
	Vertex from;
	Vertex to;
};

class DGraph {
private:
	__gnu_cxx::hash_map <std::string, Vertex *> id_to_vertex;
	__gnu_cxx::hash_map <std::string, Edge *>   id_to_edge;

	__gnu_cxx::hash_map <std::string, Vertex_Label *> vertex_label_table;
	__gnu_cxx::hash_map <std::string, Edge_Label *>     edge_label_table;

	__gnu_cxx::hash_set <std::pair <std::string, std::string>> is_connected;

public:
	DGraph();
	// TODO: 각종 함수들을 추가해야 함
};

// TODO: undirected graph에 대해서도 자료구조 선언이 필요
class UGraph {
};

#endif // GRAPH_ANALYSIS_TOOL_GRAPH_H
