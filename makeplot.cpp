#include "makeplot.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <Python.h>
#define MAX_BUF 100

namespace snu {

	void make_plot(DSGraph *graph, Plot *plot) {
		std::ofstream out;

		/* label-vertex */
		out.open("./pyplot/label-vertex.txt");

		unsigned int n = graph->id_to_vertex.size();
		typedef std::pair <std::string *, unsigned int> label_vertex;
		std::vector <label_vertex> lv;
		lv.reserve(n);
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++) {
			auto vlabel = it->second;
			lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
		}

		std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

		for(auto it = lv.begin(); it != lv.end(); it++)
			out << *(it->first) << " " << it->second << std::endl;

		out.close();

		/* indegree */
		out.open("./pyplot/indegree.txt");

		std::vector <unsigned int> degree;
		degree.reserve(n);
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			degree.push_back((*it->second).indegree);
		
		std::sort(degree.begin(), degree.end());
		for(auto it = degree.begin(); it != degree.end(); it++)
			out << *it << " ";

		out.close();

		/* outdegree */
		out.open("./pyplot/outdegree.txt");

		degree.clear();
		degree.reserve(n);
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			degree.push_back((*it->second).edges.size());
		
		std::sort(degree.begin(), degree.end());
		for(auto it = degree.begin(); it != degree.end(); it++)
			out << *it << " ";

		out.close();

		/* pyplot 
		Py_Initialize();
		printf("aaa\n");
		PyObject *main_module = PyImport_AddModule("__main__");
		printf("bbb\n");
		PyObject *main_dict = PyModule_GetDict(main_module);
		printf("ccc\n");
		char filename[] = "plot.py";
		printf("ddd\n");
		FILE *fp = fopen(filename, "r");
		printf("eee\n");
		PyRun_File(fp, filename, 1, main_dict, main_dict);
		printf("fff\n");
		fclose(fp);
		printf("ggg\n");
		Py_Finalize();
		printf("hhh\n");
*/
		plot->makeplot = true;
	}

	void make_plot(USGraph *graph, Plot *plot) {
		std::ofstream out;

		/* label-vertex */
		out.open("./pyplot/label-vertex.txt");

		unsigned int n = graph->id_to_vertex.size();
		typedef std::pair <std::string *, unsigned int> label_vertex;
		std::vector <label_vertex> lv;
		lv.reserve(n);
		for(auto it = graph->vlabel_to_class.begin(); it != graph->vlabel_to_class.end(); it++) {
			auto vlabel = it->second;
			lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
		}

		std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

		for(auto it = lv.begin(); it != lv.end(); it++)
			out << *(it->first) << " " << it->second << std::endl;

		out.close();

		/* degree */
		out.open("./pyplot/degree.txt");

		std::vector <unsigned int> degree;
		degree.reserve(n);
		for(auto it = graph->id_to_vertex.begin(); it != graph->id_to_vertex.end(); it++)
			degree.push_back((*it->second).indegree);
		
		std::sort(degree.begin(), degree.end());
		for(auto it = degree.begin(); it != degree.end(); it++)
			out << *it << " ";

		out.close();

		/* pyplot *//*
		char filename[] = "plot.py";
		Py_Initialize();
		FILE *fp = _Py_fopen(filename, "r");
		PyRun_SimpleFile(fp, filename);
		Py_Finalize();
*/
		plot->makeplot = true;
	}
}
