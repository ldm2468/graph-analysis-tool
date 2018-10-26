#ifndef PARSE_H
#define PARSE_H

#include <string>
#include "graph.h"

namespace snu {
	DSGraph *parse_DSGraph(std::string file_path);
	USGraph *parse_USGraph(std::string file_path);
	static DSGraph *parse_snu_DSGraph(std::string file_path);
	static DSGraph *parse_net_DSGraph(std::string file_path);
}

#endif // PARSE_H
