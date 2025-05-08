.PHONY: clean

all: premake exe

premake: bin

bin:
	mkdir -p $@

exe: bin/trim

bin/trim: src/main.cxx
	${CXX} -o $@ $< -std=c++17 -DDEBUG -Og -g -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wunreachable-code

clean:
	${RM} -f bin
