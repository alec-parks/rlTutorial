SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:.cpp=.o)
TARGET=tuto

#compiler options : add debug information in debug mode
#optimize speed and size in release mode
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	CFLAGS=-g
else
	CFLAGS=-O2 -s
endif

ifeq ($(shell sh -c 'uname -s'),Linux)
   LIBFLAGS=-L. -ltcod_debug -ltcodxx_debug -Wl,-rpath=.
else
   LIBFLAGS=-Llib -ltcod-mingw-debug -static-libgcc -static-libstdc++ -mwindows
endif

debug : $(TARGET)
release : $(TARGET)


$(TARGET) : $(OBJS)
	g++ $(OBJS) -o ${TARGET} -Wall $(LIBFLAGS) $(CFLAGS) -Iinclude

src/main.hpp.gch : src/*.hpp
	g++ src/main.hpp -Iinclude -Wall

src/%.o : src/%.cpp src/main.hpp.gch
	g++ $< -c -o $@ -std=c++11 -Iinclude -Wall $(CFLAGS)

clean :
	rm -f src/main.hpp.gch $(OBJS) $(TARGET)
