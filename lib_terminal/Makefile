CXX = g++
CXXFLAGS = -Wall -std=c++17

# Target: Create the static library
libterminal.a: Terminal.o
	ar rcs libterminal.a Terminal.o

Terminal.o: Terminal.cpp Terminal.h
	$(CXX) $(CXXFLAGS) -c Terminal.cpp

clean:
	rm -f *.o *.a