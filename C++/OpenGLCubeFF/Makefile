.PHONY: clean

EXE_DIR = bin
OBJ_DIR = obj
SRC_DIR = .
EXE = $(EXE_DIR)/GLTest
DIST_DIR = dist
APP_DIR = $(DIST_DIR)/GLTest.app
DIST_EXE_DIR = $(APP_DIR)/Contents/MacOS

UNAME_S = $(shell uname -s)

WARNINGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wno-deprecated-declarations
OPTIMIZE = -Og
DEBUG = -g -DDEBUG
CXX_STD = -std=c++17

LIB_INCLUDES =
ifeq ($(UNAME_S),Darwin)
LIBRARIES = -framework OpenGL -framework GLUT -lm
else
LIBRARIES = -lGL -lGLU -lglut -lm
endif
MAIN_SRC = $(SRC_DIR)/main.cxx
MAIN_OBJ = $(OBJ_DIR)/main.o

$(EXE): $(MAIN_OBJ)
	$(CXX) -o $@ $^ $(LIBRARIES)

dist: $(EXE)
	mkdir -p "$(DIST_EXE_DIR)"
	cp "$(EXE)" "$(DIST_EXE_DIR)"/

$(EXE_DIR):
	mkdir -p "$(EXE_DIR)"

$(OBJ_DIR):
	mkdir -p "$(OBJ_DIR)"

$(MAIN_OBJ): $(MAIN_SRC) $(EXE_DIR) $(OBJ_DIR)
	$(CXX) -c -o $@ $< $(LIB_INCLUDES) $(WARNINGS) $(OPTIMIZE) $(DBEUG) $(CXX_STD)

clean:
	rm -f "$(EXE)" "$(OBJ_DIR)"/*.o
	rm -rf "$(APP_DIR)"
