CXX = g++
CPPFLAGS = -g -Wall --std=c++11

counting: Hashtable.o counting.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

Hashtable.o: Hashtable.cpp Hashtable.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	-@rm -rf *.o counting
