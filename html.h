#ifndef HTML_H
#define HTML_H

#include "stat.h"
#include "plot.h"

namespace snu {

	void make_html(const char *name, DSResult *result, Plot *plot);
	void make_html(const char *name, USResult *result, Plot *plot);
}

#endif // HTML_H
