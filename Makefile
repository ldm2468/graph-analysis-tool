CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o stat.o basicstat.o countstat.o plot.o makeplot.o html.o
CXXFLAGS = -std=c++11 -Wall -O3 -I/C:/"Program Files"/MATLAB/R2018b/extern/include
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ graph_plot.lib mclmcrrt.lib mclmcr.lib

makeplot.o: graph_plot.lib
	$(CXX) $(CXXFLAGS) -c -o $@ makeplot.cpp 

graph_plot.lib: graph_plot.m
	mcc -W cpplib:graph_plot -T link:lib $^

clean:
	rm -rf $(TARGET) $(OBJECTS) graph_plot.lib graph_plot.def graph_plot.dll graph_plot.exports mccExcludedFiles.log readme.txt requiredMCRProducts.txt v2 graph_plot.h *.html matlab_plot
