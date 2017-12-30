CXX = mpicxx
CXXFLAGS = -std=c++11

objects = main.o \
    exponent-intervals.o values-range.o values-net.o time-intervals.o \
    parameters-utils.o file-utils.o machine-precision.o \
    s-approximations.o p-approximations.o approximations-utils.o approximations.o

biosensor-modeling: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o biosensor-modeling

main.o: exponent-intervals.h
exponent-intervals.o: exponent-intervals.h
values-range.o: values-range.h
values-net.o: values-net.h
time-intervals.o: time-intervals.h
machine-precision.o: machine-precision.h
parameters-utils.o: parameters-utils.h
file-utils.o: file-utils.h
approximations-utils.o: approximations-utils.h
s-approximations.o: s-approximations.h
p-approximations.o: p-approximations.h
approximations.o: approximations.h

clean:
	-rm biosensor-modeling *.o