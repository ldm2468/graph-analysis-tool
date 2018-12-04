#include "plot.h"

namespace snu {
  
	// TODO: thread-unsafe function, should be revised
	void init_plot(Plot *plot) {
		static unsigned int cnt = 0;
		plot->id = cnt++;
		plot->makeplot = false;
	}
}