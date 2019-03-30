CXX = g++
TARGET = main
OBJECTS = main.o graph.o parse.o stat.o basicstat.o connectstat.o countstat.o makeplot.o html.o
TEST = test
TEST_OBJECTS = test.o graph.o parse.o diameter.o
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS =

all: $(TARGET) $(TEST)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(TEST): $(TEST_OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJECTS) *.html pyplot/*.png __pycache__
