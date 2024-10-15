#=======================================================#
# compiler, flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall
#=======================================================#
# objects
OBJS = perlintest.o fractal.o
#=======================================================#
# SFML
SFML_INC = /opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIB = /opt/homebrew/Cellar/sfml/2.6.1/lib
#=======================================================#
# include SFML
INCLUDES = -I$(SFML_INC)
LIBS = -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system
#=======================================================#
# make target
all: perlin
#=======================================================#
# linking
perlin: $(OBJS)
	$(CXX) $(CXXFLAGS) -o perlin $(OBJS) $(LIBS)
#=======================================================#
# PerlinTest.cpp
perlintest.o: Mountain.cpp FractalPerlin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c Mountain.cpp
#=======================================================#
# PerlinNoise.cpp
fractal.o: FractalPerlin.cpp FractalPerlin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c FractalPerlin.cpp
#=======================================================#
# clean
clean:
	rm -f *.o perlin