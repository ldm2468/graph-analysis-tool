#ifndef HTML_H
#define HTML_H

#include "stat.h"
#include "plot.h"


namespace snu {

    void makeHtml(const char *name, DSResult *result, Plot *plot);
    void makeHtml(const char *name, USResult *result, Plot *plot);
}

#endif // HTML_H

