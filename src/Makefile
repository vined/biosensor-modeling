# Think of using separate folders
CXXFLAGS = -std=c++11
objects = main.o exponent-intervals.o

biosensor-modeling: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o biosensor-modeling

main.o: exponent-intervals.h
exponent-intervals.o: exponent-intervals.h

clean:
	-rm biosensor-modeling *.o