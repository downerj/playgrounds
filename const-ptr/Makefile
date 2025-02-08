.PHONY: clean

EXE = test

${EXE}: main.cxx
	${CXX} -o $@ $< -Wall -Wextra -Wpedantic -std=c++17

clean:
	rm -f ${EXE}
