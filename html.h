#ifndef HTML_H
#define HTML_H

#include "basicstat.h"
#include "plot.h"

namespace snu {

	void make_html(char *name, DSResult *result, Plot *plot);
	void make_html(char *name, USResult *result, Plot *plot);
}

#endif // HTML_H
