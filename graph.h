#ifndef GRAPH_ANALYSIS_TOOL_GRAPH_H
#define GRAPH_ANALYSIS_TOOL_GRAPH_H

// TODO: stl의 unordered_map을 대체할 해시테이블 개발 필요
// licensed under GNU General Public License v3.0
#include <unordered_map>

// TODO: 다른 종류의 graph도 추후에 개발 필요
class DSGraph; // directed simple graph having no loop, no multiple edge


class DSGraph { // directed simple graph
private:
	unordered_map <VId, Vertex *> id_to_vertex;
	unordered_map <EId, Edge *>   id_to_edge;

	unordered_map <VLbl, Vertex_Label *> vertex_label_table;
	unordered_map <ELbl, Edge_Label *>     edge_label_table;

	unordered_map <std::pair <VId, VId>, Edge *> id_pair_to_edge;

public:
	// TODO: 생성자, 파괴자, 복사 생성자, 각종 method들에 대한 생성 필요
	DSGraph();

	void insert_vertex(VId id, VLbl label);
	void insert_edge(EId id, ELbl label, VId from, VId to, int wgt);
	void delete_vertex(VId id);
	void delete_edge(EId id);
};

#endif // GRAPH_ANALYSIS_TOOL_GRAPH_H
