CC= g++

INCDIR = ../KillerbyteGameEngine/src/
ENGINE_LIB_FLAG = ../KillerbyteGameEngine/
GLEW_LIB_FLAG = ../KillerbyteGameEngine/src/glew/lib/linux/x64
LIBFLAGS = -L$(ENGINE_LIB_FLAG) -L$(GLEW_LIB_FLAG)

CXXFLAGS= -Wall -I$(INCDIR)

TestTriangle: TestTriangle.o
			$(CC) $(CFLAGS)  TestTriangle.o 

TestTriangle.o: TestTriangle.cpp
			$(CC) $(CFLAGS) $(LIBFLAGS) TestTriangle.cpp -lX11 -lGL -lGLU -lGLEW -lKillerbyte
	
clean: 
			rm -f *.o; rm TestTriangle
