CXX = g++
CPPFLAGS = -g -Wall -std=c++11

coloring: coloring.o
	$(CXX) $(CPPFLAGS) $^ -o $@

coloring.o: coloring.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	-@rm -rf *.o coloring
