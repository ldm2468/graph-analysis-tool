#ifndef STAT_H
#define STAT_H

#include "graph.h"

/*
 * --- Class Stat ---
 * CommonStat / DirectedStat / UndirectedStat
 * 
 * Analyze stats for a given graph, then store its results.
 * Stored results can be written to an HTML file using 'writeToHTML(...)'
 * or exported to a separate file using 'writeToFile(...)'
 * 
 * --- BASIC USAGE ---
 * 
 * calculate() -> writeToHTML() or writeToFile()
 * 
 * 
 * --- HOW TO CREATE A NEW STAT ---
 * 
 * 1. Determine base class to derive from
 *    - DirectedStat: The stat can only be calculated for directed graphs
 *    - UndirectedStat: The stat can only be calculated for undirected graphs
 * 		- CommonStat: The stat can be calculated for both directed and undirected graphs
 * 
 * 2. Create a new class that inherits the chosen base class
 * 		- refer to 'ClosenessCentrality.h' for an example
 * 
 * 3. Override 'statName()' to return a name for the stat
 * 		- used for debug logging purposes.  
 * 
 * 4. Override 'calculateStat(...)' to analyze the graph and store the results
 * 		in the class's private members. 
 * 		(Name of the function to override can vary depending on the base class - check list below)
 * 		- CommonStat:			calculateStat()
 * 		- DirectedStat: 	calculateDirectedStat()
 * 		- UndirectedStat: calculateUndirectedStat()
 * 
 * 5. Override 'writeToHTMLStat(...)' to write results into an HTML file.
 * 		- Note that basic header/footer can be omitted.
 * 			writeToHTML() only writes a portion of the whole HTML file.
 * 
 * 6. Override 'writeToFileStat(...)' to write results into a separate file. (optional)
 * 		- Useful for unit testing.
 * 		- For centrality measures, testers/test_centrality.py can be used for comparison with
 * 			SNAP. (stanford's graph analysis library)
 * 
 * 7. Add the new stat to a StatAnalyzer
 * 		- StatAnalyzer will call 'calculate(...) & writeToFile(...)' for the input graph. 
 * 		- currently being handled at main.cpp (2022.07.04)
 * 		- (at main.cpp) add to 'common_stats' or 'directed_only_stats' or 'undirected_only_stats'
 * 
 * 8. Add the new stat to HTML
 * 		- currently being handled at main.cpp (2022.07.04)
 * 		- (at main.cpp) add to 'html_order'
 * 
 */

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
