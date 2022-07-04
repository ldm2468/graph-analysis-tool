#ifndef PARSE_H
#define PARSE_H

#include "graph.h"
#include <string>
#include <memory>

namespace snu {

    const int PARSE_SUCCESS = 0;
    const int PARSE_FAILURE_NO_INPUT = 1;
    const int PARSE_FAILURE_INVALID_INPUT = 2;
    const int PARSE_FAILURE_INVALID_FILETYPE = 3;
    const int PARSE_FAILURE_ADD_VERTEX = 4;
    const int PARSE_FAILURE_ADD_EDGE = 5;

    std::shared_ptr<Graph> parseFile(std::string input_path, bool directed);
    int parseDSGraph(std::string file_path, DSGraph& graph);
    int parseUSGraph(std::string file_path, USGraph& graph);
}

#endif // PARSE_H

