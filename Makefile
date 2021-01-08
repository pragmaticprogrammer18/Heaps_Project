CC     = /usr/local/bin/g++
CFLAGS =  -g -ansi -Wall

FILE = output.txt


# Project-specific macros
PROJ   = Driver.out
DOTOS  = Driver.o Heap.o PinHit.o MinValueHeap.o MaxValueHeap.o

HEAP = Heap.h Heap.cpp
PINHIT = PinHit.h PinHit.cpp
MIN = MinValueHeap.h MinValueHeap.cpp
MAX = MaxValueHeap.h MaxValueHeap.cpp

INPUT = Input1.txt

# RULES FOR LINKING AND RUNNING EXECUTABLES
######################################################################

all: $(DOTOS)
	$(CC) $(CFLAGS) $(DOTOS)

# Runs the project executable
run: $(PROJ) $(FLAG)
	./$(PROJ) $(INPUT) $(FLAG)

# Runs the project executable via valgrind to check for memory leaks
runV: $(PROJ)
	valgrind ./$(PROJ) $(INPUT) $(FLAG)

tofile: all
	a.out > $(FILE) 



# RULES FOR COMPILATION
######################################################################
Driver.o: Driver.cpp
	$(CC) $(CFLAGS) -c Driver.cpp

Heap.o:  $(HEAP) $(PINHIT)
	$(CC) $(CFLAGS) -c Heap.cpp

MinValueHeap.o:  $(MIN) $(HEAP)
	$(CC) $(CFLAGS) -c MinValueHeap.cpp

MaxValueHeap.o:  $(MAX) $(HEAP)
	$(CC) $(CFLAGS) -c MaxValueHeap.cpp

PinHit.o: $(PINHIT) 
	$(CC) $(CFLAGS) -c PinHit.cpp

# RULES FOR CLEANING UP EXTRA, UNNECESSARY, AND OLD FILES
######################################################################

.PHONY: clean cleaner cleanest c

# "clean" removes temporary files (~) and autosaves (#)
clean:
	rm -f *# *~

# "cleaner" removes everything from "clean" along with any .o files
cleaner: clean
	rm -f *.o

# "cleanest" removes everything from "cleaner" along with the executable,
#     any core dump, and any .h.gch files that may have been created
cleanest: cleaner
	rm -f core*; rm -f $(PROJ); rm -f *.h.gch

# "c" is a shortcut for running the "cleanest" rule
c: cleanest


# OTHER RULES 
######################################################################
.PHONY: make
make: Makefile
	emacs Makefile



