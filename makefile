CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL
OBJS = main.o
PROG = sdlsnake
CXX = g++

all: $(PROG)

# Creating .o files for all components
%.o: src/%.h src/%.cpp
	$(CXX) $(CFLAGS) -c -s $<

# Linking and compiling the program
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

clean:
	rm $(PROG) *.o
