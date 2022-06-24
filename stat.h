#ifndef STAT_H
#define STAT_H

#include "graph.h"

namespace snu {
	class Stat {
		public:
			// Name of the stat used for filenames, logs ...
			virtual std::string statName() = 0;
			
			bool getSuccess();
			void writeToHTML(FILE* fp, bool directed);
			void writeToFile(std::string graph_name, bool directed);

		protected:
			virtual void writeToHTMLStat(FILE* fp, bool directed) = 0;
			virtual void writeToFileStat(std::string graph_name, bool directed) {}
			bool success = false;
	};

	// stats that apply to both USGraph and DSGraph
	class CommonStat : public Stat {
		public:
			// returns true on success
			bool calculate(Graph &graph);

		protected:
			virtual bool calculateStat(Graph &graph) = 0;
	};

	// stats that apply to only DSGraph
	class DirectedStat : public Stat {
		public:
			// returns true on success
			bool calculateDirected(DSGraph &graph);

		protected:
			virtual bool calculateDirectedStat(DSGraph &graph) = 0;
	};

	class UndirectedStat : public Stat {
		public:
			// returns true on success
			bool calculateUndirected(USGraph &graph);

		protected:
			virtual bool calculateUndirectedStat(USGraph &graph) = 0;
	};
}

#endif // STAT_H
