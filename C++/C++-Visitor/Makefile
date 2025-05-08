.PHONY: clean

EXE_DIR = bin
EXE = enemies
WARNS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors
CXX_STD = -std=c++17
OPTIMIZE = -Og
DEBUG = -DDEBUG -g

MAIN_CXX = main.cxx

${EXE_DIR}/${EXE}: ${MAIN_CXX} ${EXE_DIR}
	${CXX} -o "$@" $< ${WARNS} ${CXX_STD} ${OPTIMIZE} ${DEBUG}

${EXE_DIR}:
	mkdir -p "$@"

clean:
	rm -rf "${EXE_DIR}"
