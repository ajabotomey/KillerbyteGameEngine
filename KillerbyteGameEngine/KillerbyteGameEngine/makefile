CC= g++
utilObjs = MainLinux.o Platform.o PlatformLinux.o Game.o Camera.o Matrix44.o
INCDIR = /usr/include/GL
CFLAGS= -c -Wall -I$(INCDIR) -I"glew/include"

libKillerbyte.a: $(utilObjs)
			ar rc $@ $(utilObjs)
			ranlib $@

MainLinux.o: src/MainLinux.cpp
			$(CC) $(CFLAGS) src/MainLinux.cpp
				
Platform.o: src/Platform.cpp src/PlatformLinux.cpp
			$(CC) $(CFLAGS) src/Platform.cpp
			
PlatformLinux.o: src/PlatformLinux.cpp
			$(CC) $(CFLAGS) src/PlatformLinux.cpp -lX11 -lGL -lGLU
			
Game.o: src/Game.cpp
			$(CC) $(CFLAGS) src/Game.cpp
			
Camera.o: src/Camera.cpp
			$(CC) $(CFLAGS) src/Camera.cpp
			
Matrix44.o: src/Matrix44.cpp
			$(CC) $(CFLAGS) src/Matrix44.cpp
			
clean: 
			rm -f *.o; rm libKillerbyte.a