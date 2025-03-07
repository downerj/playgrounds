.PHONY: clean

EXE = a.exe
MAIN_CXX = main.cxx

WARNINGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors
CXX_STD = -std=c++17
OPTIMIZE = -Og -g
DEBUG = -DDEBUG

${EXE}: ${MAIN_CXX}
	${CXX} -o "$@" $< ${WARNINGS} ${CXX_STD} ${OPTIMIZE} ${DEBUG}

clean:
	rm -f ${EXE}
