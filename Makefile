CXX = g++
TARGET = <source code file>
OBJECTS = <source code file>.o graph.o parse.o stat.o basicstat.o connectstat.o countstat.o plot.o makeplot.o html.o
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJECTS) *.html pyplot/*.png __pycache__
