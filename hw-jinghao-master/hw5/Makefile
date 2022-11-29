CXX = g++
CPPFLAGS = -g -Wall --std=c++11

bayes: bayes.o
	$(CXX) $(CPPFLAGS) $^ -o $@

bayes.o: bayes.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	-@rm -rf *.o bayes
