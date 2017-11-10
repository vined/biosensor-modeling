
CXXFLAGS = -std=c++11
objects = main.o \
    exponent-intervals.o values-range.o values-net.o machine-precision.o time-intervals.o \
    approximations-utils.o approximations.o \
    output-utils.o

biosensor-modeling: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o biosensor-modeling

main.o: exponent-intervals.h
exponent-intervals.o: exponent-intervals.h
values-range.o: values-range.h
values-net.o: values-net.h
time-intervals.o: time-intervals.h
machine-precision.o: machine-precision.h
output-utils.o: output-utils.h
approximations-utils.o: approximations-utils.h
s-approximations.o: s-approximations.h
p-approximations.o: p-approximations.h
approximations.o: approximations.h

clean:
	-rm biosensor-modeling *.o