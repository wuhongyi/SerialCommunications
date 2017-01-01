### Makefile --- 
## 
## Description: 
## Author: Hongyi Wu(吴鸿毅)
## Email: wuhongyi@qq.com 
## Created: 日 1月  1 19:54:00 2017 (+0800)
## Last-Updated: 日 1月  1 21:25:39 2017 (+0800)
##           By: Hongyi Wu(吴鸿毅)
##     Update #: 3
## URL: http://wuhongyi.cn 

OBJ = pb5

CXX=g++        
CXXFLAGS:=-std=c++11 -g -Wall -I. 
ROOTLIBS = $(shell root-config --libs) -lGui
ROOTINC = -I$(shell root-config --incdir) 
CXXFLAGS+=$(ROOTINC)


INCLUDES:=MainFrame.hh 

OBJECTS:=MainFrame.o main.o MainDict.o 

SRCS:=MainFrame.cc main.cc MainDict.cc

all: $(OBJ)


$(OBJ): $(SRCS) $(OBJECTS) $(INCLUDES)
	$(CXX) -o  $@  $(OBJECTS) $(CXXFLAGS) $(ROOTLIBS)

%.o: %.cxx 
	$(CXX) $(CXXFLAGS) -c $< 
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< 
MainDict.cc:MainFrame.hh MainLinkdef.h
	rootcint -f $@ -c $^


clean: 
	rm -f *.o *~ $(OBJ) *Dict*

very-clean:
	rm -f $(OBJ) *.o *~

.PHONY: clean very-clean

######################################################################
### Makefile ends here
