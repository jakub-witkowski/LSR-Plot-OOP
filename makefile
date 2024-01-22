CC=g++
CXXFLAGS=-g
CFLAGS=-std=c++11 `root-config --cflags`
LDFLAGS=`root-config --libs`
SOURCES=main.cpp tdata.cpp tpolynomial.cpp tsegment.cpp tplot.cpp

all: compile run

compile: $(SOURCES)
	$(CC) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o plot $(CFLAGS)
#	$(CC) $(SOURCES) -o plot $(CFLAGS)
run:
	./plot 1050.csv