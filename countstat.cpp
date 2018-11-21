#include "countstat.h"

namespace snu {
	void count_stat(DSGraph *graph, DSResult *result) {
		// TODO
		result->four_tour_count = 0;

		result->countstat = true;
	}

	void count_stat(USGraph *graph, USResult *result) {
		// TODO
		result->four_tour_count = 0;
		result->wedge_count = 0;
		result->claw_count = 0;
		result->triangle_count = 0;
		result->square_count = 0;

		result->countstat = true;
	}
}