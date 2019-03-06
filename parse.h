#ifndef PARSE_H
#define PARSE_H

#include "graph.h"
#include <string>


namespace snu {

    DSGraph *parse_DSGraph(std::string file_path);
    USGraph *parse_USGraph(std::string file_path);
}

#endif // PARSE_H

