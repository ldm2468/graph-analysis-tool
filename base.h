#ifndef BASE_H
#define BASE_H

// TODO: stl의 list를 대체할 연결리스트 개발 필요
// licensed under GNU General Public License v3.0
#include <list>

typedef int VId;  // vertex id
typedef int EId;  // edge   id
typedef int VLbl; // vertex label
typedef int ELbl; // edge   label

typedef int IWgt; // integer type weight

struct Vertex_Label;
struct Edge_Label;
struct Vertex;
struct Edge;

struct Vertex_Label {
	VLbl label;
	std::list <Vertex *> vertices;
};

struct Edge_Label {
	ELbl label;
	std::list <Edge *> edges;
};

struct Vertex {
	VId id;
	std::list <Vertex_Label *> labels;
	std::list <Edge *> edges;
};

struct Edge {
	EId id;
	std::list <Edge_Label *> labels;
	Vertex * from;
	Vertex * to;
	IWgt weight; // TODO: 가중치에 대해서 int 뿐만 아니라 long long이나 double 등 여러 가지 구현 필요, typedef로 관리 필요
};

#endif // BASE_H
