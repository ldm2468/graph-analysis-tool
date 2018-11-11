CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o basicstat.o countstat.o
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJECTS)
