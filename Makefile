# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc  

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm 

# add header files here
HDRS := src/headers/structs.h src/headers/common.h src/headers/main.h \
src/headers/init.h src/headers/defs.h src/headers/input.h src/headers/drawIssue.h \
src/headers/texture.h src/headers/stage.h src/headers/map.h src/headers/fileOperation.h \
src/headers/camera.h src/headers/move.h src/headers/check.h

# add source files here
SRCS := main.c src/init.c src/input.c src/drawIssue.c src/texture.c src/stage.c src/map.c src/fileOperation.c src/camera.c src/move.c src/check.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

showfont: showfont.c Makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)
	rm *.o

glfont: glfont.c Makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)
	rm *.o

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	rm *.o

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#    $(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean