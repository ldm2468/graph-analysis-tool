#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_map>

namespace snu {

	class Graph; // graph interface

	class DSGraph; //   directed simple graph
	//class DMGraph; //   directed multi  graph
	class USGraph; // undirected simple graph
	//class UMGraph; // undirected multi  graph
	// simple: no multiple edges

	class Graph {
	protected:
		typedef int VId;  // vertex id
		typedef int EId;  // edge   id
		typedef int VLbl; // vertex label
		typedef int ELbl; // edge   label
		typedef int Wgt; // integer type weight
		typedef int Lblc; // label count 
		//typedef long long LWgt; // long long type weight
		//typedef double DWgt; // double type weight

		class Vertex;
		class Edge;
		class Vertex_Label;
		class Edge_Label;
		//class IEdge;
		//class LEdge;
		//class DEdge;

		class Vertex {
		private:
			VId id;
			std::list <Vertex_Label *> labels;
			std::list <Edge *> edges;
		};

		class Edge {
		private:
			EId id;
			std::list <Edge_Label *> labels;
			Vertex * from;
			Vertex * to;
		};

		class Vertex_Label {
		private:
			VLbl label;
			std::list <Vertex *> vertices;
		};

		class Edge_Label {
		private:
			ELbl label;
			std::list <Edge *> edges;
		};
		
		std::unordered_map <VId, Vertex *> id_to_vertex;
		std::unordered_map <EId, Edge *>   id_to_edge;

		std::unordered_map <VLbl, Vertex_Label *> vertex_label_table;
		std::unordered_map <ELbl, Edge_Label *>     edge_label_table;

		//std::unordered_map <std::pair <VId, VId>, Edge *> id_pair_to_edge;

	public:
		Graph(); // constructor
		~Graph(); // destructor
		void add_vertex(VId id, Lblc num, VLbl lbl[]); // add vertex
		void add_edge(EId id, Lblc num, ELbl lbl[], VId from, VId to, Wgt weight); // add edge

		// friend function
		friend int * basicstat(Graph graph, int stat[]);
	};



	/*class DSGraph: public Graph { // directed simple graph
	};*/

	/*class DMGraph: public Graph {
	};*/

	/*class USGraph: public Graph {
	};*/

	/*class UMGraph: public Graph {
	};*/
}

#endif // GRAPH_H