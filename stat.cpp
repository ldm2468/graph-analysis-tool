#include "stat.h"

namespace snu {

	bool Stat::getSuccess() {
		return success;
	}

	void Stat::writeToHTML(FILE* fp, bool directed) {
		if (success)
			writeToHTMLStat(fp, directed);
		else
			fprintf(stderr, "writeToHTML called on failed stat %s\n", statName().c_str());
	}

	void Stat::writeToFile(std::string graph_name, bool directed) {
		if (success)
			writeToFileStat(graph_name, directed);
		else
			fprintf(stderr, "writeToFile called on failed stat %s\n", statName().c_str());
	}

	bool CommonStat::calculate(Graph &graph) {
		success = calculateStat(graph);
		return success;
	}

	bool DirectedStat::calculateDirected(DSGraph &graph) {
		success = calculateDirectedStat(graph);
		return success;
	}

	bool UndirectedStat::calculateUndirected(USGraph &graph) {
		success = calculateUndirectedStat(graph);
		return success;
	}
}
