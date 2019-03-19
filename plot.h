#ifndef PLOT_H
#define PLOT_H


namespace snu {

    typedef struct Plot {
        unsigned int id;
        bool makeplot;
    } Plot;
    
    void initPlot(Plot *plot);
}

#endif // PLOT_H

