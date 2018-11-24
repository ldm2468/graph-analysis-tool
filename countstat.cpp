#include "countstat.h"

namespace snu {
	void count_stat(DSGraph *graph, DSResult *result) {
		// TODO: four_tour_count
		// result->four_tour_count = 0;

		result->countstat = true;
	}

	void count_stat(USGraph *graph, USResult *result) {
		// TODO: square_count, four_tour_count
		result->wedge_count = 0;
		result->claw_count = 0;
		result->triangle_count = 0;
		// result->square_count = 0;
		// result->four_tour_count = 0;

		result->countstat = true;
	}
}