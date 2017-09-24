# Think of using separate folders
CXXFLAGS = -std=c++11
objects = main.o exponent-values-net-generator.o

biosensor-modeling: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o biosensor-modeling

main.o: exponent-values-net-generator.h
exponent-values-net-generator.o: exponent-values-net-generator.h

clean:
	-rm biosensor-modeling $(objects)