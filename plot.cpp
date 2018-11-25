#include "plot.h"

namespace snu {
  
	void init_plot(Plot *plot) {
		static unsigned int cnt = 0;
		plot->id = cnt++;
		plot->makeplot = false;
	}
}