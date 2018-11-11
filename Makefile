CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o basicstat.o countstat.o
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS =

all: $(TARGET) plot

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

plot: plot.m
	mcc -m $^

clean:
	rm -rf $(TARGET) $(OBJECTS)
