.PHONY: clean

EXE = a.out

release: DEBUG =
release: ${EXE}

debug: DEBUG = -g -DDEBUG
debug: ${EXE}

${EXE}: main.c++
	${CXX} -o $@ $< -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wunreachable-code ${DEBUG}

clean:
	${RM} ${EXE}
