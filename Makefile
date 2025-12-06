# Makefile
CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -L./lib_terminal -lterminal
TARGET = orphan_process
SRC = src/main.cpp src/SystemLog.cpp src/KernelTree.cpp src/Daemon.cpp

OBJ = $(SRC:.cpp=.o)

all: library game

library:
	cd lib_terminal && $(MAKE)

game: $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(TARGET).exe
	cd lib_terminal && $(MAKE) clean