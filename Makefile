CC=g++

OPENGLLIB= -framework OpenGL 
# OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=a3_anim
SRCS=07_hierarchical_modelling.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp texture.cpp
INCLUDES=gl_framework.hpp shader_util.hpp 07_hierarchical_modelling.hpp hierarchy_node.hpp parameters.cpp shape_functions.cpp cuboid_definitions.cpp arrays.cpp texture.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
