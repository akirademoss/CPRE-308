EXE = main

CPPSRC := $(wildcard *.cpp) $(wildcard */*.cpp)
CPPOBJ := $(patsubst %.cpp,%.cpp.o,$(CPPSRC))

CSRC := $(wildcard *.c) $(wildcard */*.c)
COBJ := $(patsubst %.c,%.c.o,$(CSRC))


CFLAGS = -I. -Wall
CXXFLAGS = -I. -Wall -std=c++0x -g -ldl
LFLAGS = -rdynamic -ldl 

all: $(EXE)
	
$(EXE): $(CPPOBJ) $(COBJ)
	g++ -o $@ $^ $(LFLAGS)

%.cpp.o: %.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

%.c.o: %.c
	gcc $(CFLAGS) -o $@ -c $<


clean:
	rm -f $(CPPOBJ)
	rm -f $(COBJ)
	rm -f main

.PHONY: all $(SUBDIRS)





