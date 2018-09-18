#ifndef GRAPH_H
#define GRAPH_H

// licensed under GNU General Public License v3.0
#include <list>
#include <unordered_map>
// TODO: STL을 대체할 연결리스트와 해시테이블 개발 필요

class Graph; // graph interface

class DSGraph; //   directed simple graph
class DMGraph; //   directed multi  graph
class USGraph; // undirected simple graph
class UMGraph; // undirected multi  graph
// simple: no multiple edges

class Graph {
protected:
	typedef int VId;  // vertex id
	typedef int EId;  // edge   id
	typedef int VLbl; // vertex label
	typedef int ELbl; // edge   label

	typedef int IWgt; // integer type weight
	typedef long long LWgt; // long long type weight
	typedef double DWgt; // double type weight

	class Vertex_Label;
	class Edge_Label;

	class Vertex;

	class Edge;
	class IEdge;
	class LEdge;
	class DEdge;

	class Vertex_Label {
	private:
		VLbl label;
		List <Vertex *> vertices;
	};

	class Edge_Label {
	private:
		ELbl label;
		List <Edge *> edges;
	};

	class Vertex {
	private:
		VId id;
		List <Vertex_Label *> labels;
		List <Edge *> edges;
	};

	class Edge {
	public:
		EId id;
		List <Edge_Label *> labels;
		Vertex * from;
		Vertex * to;
	};

	class IEdge : Edge {
	private:
		IWgt weight;
	};

public:
};

class DSGraph: public Graph { // directed simple graph
private:


private:
	unordered_map <VId, Vertex *> id_to_vertex;
	unordered_map <EId, Edge *>   id_to_edge;

	unordered_map <VLbl, Vertex_Label *> vertex_label_table;
	unordered_map <ELbl, Edge_Label *>     edge_label_table;

	unordered_map <std::pair <VId, VId>, Edge *> id_pair_to_edge;

public:
	DSGraph();
	~DSGraph();
	DSGraph(const DSGraph & dsg);

	void insert_vertex(VId id, VLbl label);
	void insert_edge(EId id, ELbl label, VId from, VId to, IWgt wgt);
	void delete_vertex(VId id);
	void delete_edge(EId id);

	basic_stat();
};

class DMGraph: public Graph {
};

class USGraph: public Graph {
};

class UMGraph: public Graph {
};

#endif // GRAPH_H
