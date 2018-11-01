CC = g++
TARGET = main
OBJECTS = main.o basicstat.o graph.o parse.o
CXXFLAG = -std=c++11 -Wall -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAG) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJECTS)