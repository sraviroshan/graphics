OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
GLULIB = -lGLU
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(GLULIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=transformer
SRCS=gl_framework.cpp transformer.cpp texture_utils.cpp optimus.cpp
INCLUDES=gl_framework.hpp texture_utils.h optimus.h



all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~


