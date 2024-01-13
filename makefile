CC=g++
CFLAGS=-std=c++11 `root-config --cflags`
LDFLAGS=`root-config --libs`
SOURCES=main.cpp tdata.cpp #tplot.cpp tsegment.cpp

all: compile run

compile: $(SOURCES)
	$(CC) $(SOURCES) $(LDFLAGS) -o plot $(CFLAGS)
#	$(CC) $(SOURCES) -o plot $(CFLAGS)
run:
	./plot 1050.csv