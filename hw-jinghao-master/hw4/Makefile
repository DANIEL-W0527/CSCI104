CXX = g++
CPPFLAGS = -g -Wall --std=c++11

floorplan: floorplan.o
	$(CXX) $(CPPFLAGS) $^ -o $@

floorplan.o: floorplan.cpp avlbst.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	-@rm -rf *.o floorplan
