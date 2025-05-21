.PHONY: clean

# For an explanation about automatic variables ($@, $<, $^, etc.), see:
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

COMPILE_FLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c++20
LINK_FLAGS =

# Preprocessor (-E) -> Compiler (-S) -> Assembler (-c) -> Linker

# Links object code together into one executable.

rpg.exe: main.obj intro.obj player.obj
	$(CXX) -o $@ $^ $(LINK_FLAGS)

# -c runs preprocessor, compiler & assembler (creates object code,
# which is machine code that's not yet executable).

main.obj: main.cpp intro.hpp player.hpp colors.hpp
	$(CXX) -c -o $@ $< $(COMPILE_FLAGS)

intro.obj: intro.cpp intro.hpp colors.hpp
	$(CXX) -c -o $@ $< $(COMPILE_FLAGS)

player.obj: player.cpp player.hpp colors.hpp
	$(CXX) -c -o $@ $< $(COMPILE_FLAGS)

# -E runs preprocessor only (resolves macros, #include).

# main.ipp: main.cpp
# 	$(CXX) -E -o $@ $< $(COMPILE_FLAGS)
# intro.ipp: intro.cpp
# 	$(CXX) -E -o $@ $< $(COMPILE_FLAGS)

# -S runs preprocessor and compiler (creates assembly language code).

# main.s: main.cpp
# 	$(CXX) -S -o $@ $< $(COMPILE_FLAGS)
# intro.s: intro.cpp
# 	$(CXX) -S -o $@ $< $(COMPILE_FLAGS)

clean:
	rm -f rpg.exe *.obj *.ipp *.s
