#ifndef PLOT_H
#define PLOT_H

namespace snu {

	struct Plot {
		unsigned int id;
		bool makeplot;
	};

	typedef struct Plot Plot;

	void init_plot(Plot *plot);
}

#endif // PLOT_H
