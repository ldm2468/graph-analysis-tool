CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o stat.o basicstat.o countstat.o plot.o makeplot.o html.o
LIBS = graph_plot.lib mclmcrrt.lib
MATPLOT = graph_plot.lib graph_plot.dll graph_plot.def graph_plot.exports graph_plot.h graph_plot.cpp mccExcludedFiles.log readme.txt requiredMCRProducts.txt v2
CXXFLAGS = -std=c++11 -Wall -O3
INCPATH = -I/C:/"Program Files"/MATLAB/R2018b/extern/include

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

makeplot.o: graph_plot.lib
	$(CXX) $(CXXFLAGS) $(INCPATH) -c -o $@ makeplot.cpp

graph_plot.lib: graph_plot.m
	mcc -W cpplib:graph_plot -T link:lib $^

clean:
	rm -rf $(TARGET) $(OBJECTS) $(MATPLOT) *.html matlab_plot/*.png
