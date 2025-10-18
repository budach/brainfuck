MAIN_COMPILER = g++
COMMONFLAGS = -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wpedantic -Wformat=2 -pipe -std=c++20
DEBUGFLAGS = -O0 -g3
RELEASEFLAGS = -flto=auto -march=native -mtune=native -O3 -DNDEBUG -fno-plt -fno-rtti
LDFLAGS = -Wl,-O2,--as-needed,--gc-sections,--relax

FILES = main.cpp
EXECUTABLE = brainfuck_cpp

release:
	$(MAIN_COMPILER) $(COMMONFLAGS) $(RELEASEFLAGS) -o $(EXECUTABLE) $(FILES) $(LDFLAGS)
	strip --strip-all -R .comment -R .note $(EXECUTABLE)

debug:
	$(MAIN_COMPILER) $(COMMONFLAGS) $(DEBUGFLAGS) -o $(EXECUTABLE) $(FILES)

clean:
	rm $(EXECUTABLE)