sources  := $(wildcard src/*.c)
objects  := $(sources:src/%.c=obj/%.o)

CC       := gcc
CFLAGS   := -Wall -pedantic -g

rars: $(objects)
	$(LINK.o) $^ -o $@

obj/%.o : src/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm $(wildcard obj/*.o) rars
