#include "makeplot.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#define CMD_MAX_LENGTH 30


namespace snu {

    // thread-unsafe, TODO: file path has to be like 0_label-vertex.txt depending on plot.id
    void makePlot(DSGraph *graph, Plot *plot)
    {
        std::ofstream out;

        // label-vertex
        out.open("./pyplot/label-vertex.txt");

        unsigned int n = graph->id_to_vertex.size();
        typedef std::pair<std::string*, unsigned int> label_vertex;
        std::vector<label_vertex> lv;
        lv.reserve(n);
        for (auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); ++it) {
            auto vlabel = it->second;
            lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
        }

        std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

        for (auto it = lv.begin(); it != lv.end(); ++it)
            out << *(it->first) << " " << it->second << std::endl;

        out.close();

        char cmd[CMD_MAX_LENGTH];
        sprintf(cmd, "python label-vertex.py %d", plot->id);
        system(cmd);

        // indegree
        out.open("./pyplot/indegree.txt");

        std::vector<unsigned int> degree;
        degree.reserve(n);
        for (auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); ++it)
            degree.push_back((*it->second).indegree);
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        sprintf(cmd, "python indegree.py %d", plot->id);
        system(cmd);

        // outdegree
        out.open("./pyplot/outdegree.txt");

        degree.clear();
        degree.reserve(n);
        for (auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); ++it)
            degree.push_back((*it->second).edges.size());
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        sprintf(cmd, "python outdegree.py %d", plot->id);
        system(cmd);

        plot->makeplot = true;
    }

    void makePlot(USGraph *graph, Plot *plot)
    {
        std::ofstream out;

        // label-vertex
        out.open("./pyplot/label-vertex.txt");

        unsigned int n = graph->id_to_vertex.size();
        typedef std::pair<std::string*, unsigned int> label_vertex;
        std::vector<label_vertex> lv;
        lv.reserve(n);
        for (auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); ++it) {
            auto vlabel = it->second;
            lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
        }

        std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

        for (auto it = lv.begin(); it != lv.end(); ++it)
            out << *(it->first) << " " << it->second << std::endl;

        out.close();
        
        char cmd[CMD_MAX_LENGTH];
        sprintf(cmd, "python label-vertex.py %d", plot->id);
        system(cmd);

        // degree
        out.open("./pyplot/degree.txt");

        std::vector <unsigned int> degree;
        degree.reserve(n);
        for (auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); ++it)
            degree.push_back((*it->second).indegree);
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        sprintf(cmd, "python degree.py %d", plot->id);
        system(cmd);

        // pyplot
        plot->makeplot = true;
    }
}

