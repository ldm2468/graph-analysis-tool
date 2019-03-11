#ifndef PARSE_H
#define PARSE_H

#include "graph.h"
#include <string>


namespace snu {

    const int PARSE_SUCCESS = 0;
    const int PARSE_FAILURE_NO_INPUT = 1;
    const int PARSE_FAILURE_INVALID_INPUT = 2;
    const int PARSE_FAILURE_INVALID_FILETYPE = 3;
    const int PARSE_FAILURE_ADD_VERTEX = 4;
    const int PARSE_FAILURE_ADD_EDGE = 5;

    int parse_DSGraph(std::string file_path, DSGraph& graph);
    int parse_USGraph(std::string file_path, USGraph& graph);
}

#endif // PARSE_H

