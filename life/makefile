CFLAGS = -Wall -pedantic
LFLAGS = `sdl-config --libs` -lSDL
OBJS = main.o timer.o
PROG = life
CXX = g++

all: $(PROG)

# Creating .o files for all components
%.o: src/%.cpp src/%.h
	$(CXX) $(CFLAGS) -c -s $<

# Linking and compiling the program
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

clean:
	rm $(PROG) *.o
