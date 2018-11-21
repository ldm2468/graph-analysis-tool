CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o stat.o basicstat.o countstat.o plot.o html.o
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS =

all: $(TARGET) graph_plot

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

graph_plot: graph_plot.m
	mcc -W cpplib:$@ $^

clean:
	rm -rf $(TARGET) $(OBJECTS)
