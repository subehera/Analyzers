#test: test.o QC2Error.o
#	g++ -Wall test.o QC2Error.o -o test
#

SRCS=$(wildcard *.cc)
EXEC=PlotVnm.cxx
INCLUDES=$(SRCS:.cc=.h) utils.h
OBJS=$(SRCS:.cc=.o)
OBJS+=$(EXEC:.cxx=.o)

SHELL = /bin/bash

# ROOT definitions
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

CC = clang++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -O -fPIC -Wno-deprecated $(ROOTCFLAGS)
LFLAGS = -Wall $(DEBUG) -O -fPIC -Wno-deprecated $(ROOTCFLAGS)

PlotVnm: $(OBJS)
	$(CC) $(LFLAGS) ${ROOTGLIBS} ${ROOTLIBS} $^ -o $@

PlotVnm.o: $(EXEC) $(INCLUDES)
	$(CC) $(CFLAGS) $<

######

clean:
	\rm *.o PlotVnm

run:
	make
	./PlotVnm


