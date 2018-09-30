#include "graph.h"

namespace snu {

	Graph::~Graph() {
		// delete vertex, edge, vertex_label, edge_label;
		for(auto it = id_to_vertex.begin(); it != id_to_vertex.end(); it++) delete it->second;
		for(auto it = id_to_edge.begin(); it != id_to_edge.end(); it++) delete it->second;
		for(auto it = vertex_label_table.begin(); it != vertex_label_table.end(); it++) delete it->second;
		for(auto it = edge_label_table.begin(); it != edge_label_table.end(); it++) delete it->second;
	}

	void Graph::add_vertex(VId id, Lblc num, VLbl lbl[]) {
		Vertex *v = new Vertex; // create vertex class
		v->id = id; // set id
		// set labels
		// if no vertex label class then create it
		for(int i = 0; i < num; i++) {
			auto it = vertex_label_table.find(lbl[i]);
			Vertex_Label *vl;

			if(it == vertex_label_table.end()) { // no vertex label class
				vl = new Vertex_Label;
				vl->label = lbl[i];
			}
			else vl = it->second;
			
			vl->vertices.push_back(v);
			v->labels.push_back(vl);
		}
	}

	void Graph::add_edge(EId id, Lblc num, ELbl lbl[], VId from, VId to, Wgt wgt) {
		/* TODO: from과 to에 해당하는 vertex class가 존재하지 않을 경우 오류를 발생시켜야 한다. */

		Edge *e = new Edge; // create edge class
		e->id = id; // set id
		// set edge labels
		// if no edge label class then create it
		for(int i = 0; i < num; i++) {
			auto it = edge_label_table.find(lbl[i]);
			Edge_Label *el;

			if(it == edge_label_table.end()) { // no edge label class
				el = new Edge_Label;
				el->label = lbl[i];
			}
			else el = it->second;

			el->edges.push_back(e);
			e->labels.push_back(el);
		}
		e->from = id_to_vertex[from]; // set from
		e->to = id_to_vertex[to]; // set to
		e->wgt = wgt; // set weight
	}
}
