#include <stdio.h>
#include <getopt.h>
#include <chrono>
#include <memory>

#include "snugal.h"

using namespace std::chrono;

void usage(void);

template<typename T>static void printElapsedTime(const char *msg, T &t) {
  printf("%10ldms: %s\n", (duration_cast<milliseconds>(high_resolution_clock::now() - t)).count(), msg);
  t = high_resolution_clock::now();
}

int main(int argc, char* argv[]) 
{
  if (argc < 2) {
    usage();
    return 1;
  }

  bool directed = false;  // suppose given graph is undirected.
  bool file_output = false; // default: skip output of detailed files

  while (true) {
    static struct option long_options[] = {
      {"directed", 0, NULL, 'd'}, 
      {"undirected", 0, NULL, 'u'}, 
      {"help", 0, NULL, 'h'}, 
      {"file_output", 0, NULL, 'f'}, 
      {0, 0, 0, 0}
    };

    int option = getopt_long(argc, argv, "duhf", long_options, NULL);

    if (option < 0) {
      break;
    }

    switch (option) {
      case 'd':
        directed = true;
        break;

      case 'u':
        directed = false;
        break;

      case 'f':
        file_output = true;
        break;

      case 'h':
        usage();
        return 0;

      default:
        usage();
        return 1;
    }
  }

  // There exists no non-option argument.
  // That is, input file path is not given.
  if (argc <= optind) {
    fprintf(stderr, "input file is not given.\n");
    return 1;
  }

  // Suppose input file path is the first non-option argument.
  std::string input_path(argv[optind]);

  // Extract name of given graph from input path.
  std::size_t slash = input_path.rfind("/");
  if (slash == std::string::npos) {
    slash = -1;
  }

  std::size_t dot = input_path.rfind(".");
  if (dot == std::string::npos) {
    dot = input_path.length();
  }

  std::string graph_name = input_path.substr(slash+1, dot-(slash+1));

  std::vector<snu::Stat*> all_stats;
  std::vector<snu::CommonStat*> common_stats;
  std::vector<snu::DirectedStat*> directed_only_stats;
  std::vector<snu::UndirectedStat*> undirected_only_stats;

  /* Add Stats Here */
  auto basicStat = snu::BasicStat();
  auto connectStat = snu::ConnectStat();
  auto closenessCentrality = snu::ClosenessCentrality();
  auto betweennessCentrality = snu::BetweennessCentrality();
  auto eigenCentrality = snu::EigenCentrality();

  auto countStat = snu::CountStat();
  auto biconnectedComponents = snu::BiconnectedComponents();

  /* -- Add Common Stats Here (support both directed & undirected) -- */
  common_stats = {
    &basicStat,
    &connectStat,
    &eigenCentrality,
    &closenessCentrality,
    &betweennessCentrality,
  };

  /* -- Add Directed Stats Here -- */
  directed_only_stats = {
  };

  /* -- Add Undirected Stats Here -- */
  undirected_only_stats = {
    &countStat,
    &biconnectedComponents,
  };

  for (auto p : common_stats)
    all_stats.push_back(p);
  if (directed) {
    for (auto p : directed_only_stats)
      all_stats.push_back(p);
  }
  else {
    for (auto p : undirected_only_stats)
      all_stats.push_back(p);
  }

  auto t = high_resolution_clock::now();

  std::shared_ptr<snu::Graph> graph_shptr;
  std::shared_ptr<snu::DSGraph> dsgraph_shptr;
  std::shared_ptr<snu::USGraph> usgraph_shptr;

  if (directed) {
    graph_shptr = dsgraph_shptr = std::make_shared<snu::DSGraph>();
  }
  else {
    graph_shptr = usgraph_shptr = std::make_shared<snu::USGraph>();
  }
  auto& graph = *graph_shptr.get();

  int parse_status = graph.parseGraph(input_path);
  switch (parse_status) {
    case snu::PARSE_SUCCESS:
      break;

    case snu::PARSE_FAILURE_NO_INPUT:
      fprintf(stderr, "input file is not locatable.\n");
      return 1;

    case snu::PARSE_FAILURE_INVALID_INPUT:
      fprintf(stderr, "input data is invalid.\n");
      return 1;

    case snu::PARSE_FAILURE_INVALID_FILETYPE:
      fprintf(stderr, "this filetype is not supported.\n");
      return 1;

    case snu::PARSE_FAILURE_ADD_VERTEX:
    case snu::PARSE_FAILURE_ADD_EDGE:
      fprintf(stderr, "internal error\n");
      return 1;

    default:
      return 1;
  }
  printElapsedTime("parseGraph()", t);

  // calculate common stats
  for (auto commonStat : common_stats) {
    commonStat->calculate(graph);
    printElapsedTime(commonStat->statName().c_str(), t);
  }

  // calculate directed stats
  if (directed) {
    auto& dsgraph = *dsgraph_shptr.get();
    for (auto dirStat : directed_only_stats) {
      dirStat->calculateDirected(dsgraph);
      printElapsedTime(dirStat->statName().c_str(), t);
    }
  }
  // calculate undirected stats
  else {
    auto& usgraph = *usgraph_shptr.get();
    for (auto undirStat : undirected_only_stats) {
      undirStat->calculateUndirected(usgraph);
      printElapsedTime(undirStat->statName().c_str(), t);
    }
  }

  // file output
  if (file_output) {
    for (auto stat : all_stats) {
      if (stat->getSuccess()) {
        stat->writeToFile(graph_name, directed);
        printElapsedTime(("File output: " + stat->statName()).c_str(), t);
      }
    }
  }

  // plot
  snu::Plot plot(graph_name);
  snu::makePlot(graph, plot);
  printElapsedTime("makePlot()", t);

  // write to HTML
  FILE* fp = snu::openHtml(graph_name.c_str(), directed);
  std::vector<snu::Stat*> html_order;
  if (directed) {
    /* -- Set Directed Html Order Here -- */
    html_order = {
      &basicStat,
      &connectStat,
      &eigenCentrality,
      &closenessCentrality,
      &betweennessCentrality,
    };
  }
  else {
    /* -- Set Undirected Html Order Here -- */
    html_order = {
      &basicStat,
      &connectStat,
      &eigenCentrality,
      &biconnectedComponents,
      &closenessCentrality,
      &betweennessCentrality,
      &countStat,
    };
  }
  for (auto stat : html_order) {
    snu::addStatToHtml(fp, stat, directed);
  }
  snu::closeHtml(fp, plot);
  printElapsedTime("Make HTML", t);

	return 0;
}


void usage(void)
{
    printf(" usage: main <input file> [options]\n");
    printf("\n");
    printf("  options:\n");
    printf("   -d | --directed       set graph directed\n");
    printf("   -u | --undirected     set graph undirected (default)\n");
    printf("   -f | --file_output    output centrality details as seperate files\n");
    printf("   -h | --help           print this list of help\n");
    printf("\n");
    printf("   e.g. ./main some_path/some_graph.snap --directed\n");

    return;
}

