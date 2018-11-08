CC = g++
TARGET = main
OBJECTS = main.o graph.o parse.o basicstat.o countstat.o
CXXFLAG = -std=c++11 -Wall -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAG) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJECTS)