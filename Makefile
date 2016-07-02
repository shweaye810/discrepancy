CC = g++ -std=c++1y
CFLAGS = -c -g -Wall
PROG = discrepancy

$(PROG).out: $(PROG).o asp.o info.o rma.o substitude.o
	$(CC) $^ -g -o $(PROG).out

$(PROG).o: $(PROG).cpp
	$(CC) $(CFLAGS) $<

asp.o: asp.cpp asp.h
	$(CC) $(CFLAGS) asp.cpp

info.o: info.cpp info.h
	$(CC) $(CFLAGS) info.cpp

rma.o: rma.cpp rma.h
	$(CC) $(CFLAGS) rma.cpp

substitude.o: substitude.cpp substitude.h
	$(CC) $(CFLAGS) substitude.cpp

.PHONY: clean
clean:
	-rm -f *.o *.out
