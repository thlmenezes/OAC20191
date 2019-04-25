sources  := $(wildcard src/*.cpp)
objects  := $(sources:src/%.cpp=obj/%.o)

CC       := g++
CFLAGS   := -std=c++11 -Wall -pedantic -g

rars: $(objects)
	$(LINK.o) $^ -o $@

obj/%.o : src/%.cpp
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm $(wildcard obj/*.o) rars
