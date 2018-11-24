CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o stat.o basicstat.o countstat.o plot.o makeplot.o html.o
CXXFLAGS = -std=c++11 -Wall -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJECTS) *.html pyplot/*.png
