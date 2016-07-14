CC = clang++ -std=c++14 -stdlib=libc++
CFLAGS = -c -g -Wall
PROG = discrepancy

$(PROG).out: $(PROG).o asp.o info.o rma.o tokenizer.o
	$(CC) $^ -g -o $(PROG).out

$(PROG).o: $(PROG).cpp
	$(CC) $(CFLAGS) $<

asp.o: asp.cpp asp.h
	$(CC) $(CFLAGS) $<

info.o: info.cpp info.h
	$(CC) $(CFLAGS) $<

rma.o: rma.cpp rma.h
	$(CC) $(CFLAGS) $<

tokenizer.o: tokenizer.cpp tokenizer.h
	$(CC) $(CFLAGS) $< 

.PHONY: clean
clean:
	-rm -f *.o *.out
