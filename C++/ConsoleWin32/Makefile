.PHONY: clean purge

DEBUG_BUILD ?= 0

EXE_PREFIX = bin
OBJ_PREFIX = obj
EXE_SUFFIX =
OBJ_SUFFIX =
ifeq ($(DEBUG_BUILD), 0)
EXE_SUFFIX = release
OBJ_SUFFIX = release
else
EXE_SUFFIX = debug
OBJ_SUFFIX = debug
endif
EXE_DIR = $(EXE_PREFIX)/$(EXE_SUFFIX)
OBJ_DIR = $(OBJ_PREFIX)/$(OBJ_SUFFIX)
EXE = $(EXE_DIR)/console
SRC_DIR = src
WARNINGS = -Wall -Wextra -Wconversion -Wshadow -Wunreachable-code
CXX_STD = -std=c++98
OPTIMIZE =
ifeq ($(DEBUG_BUILD), 0)
OPTIMIZE =-O3
endif
DEBUG =
ifeq ($(DEBUG_BUILD), 1)
DEBUG = -DDEBUG -g
endif
MAKE_DEPS = -MMD

SOURCES = $(wildcard $(SRC_DIR)/*.cxx)
OBJECTS = $(patsubst $(SRC_DIR)/%.cxx, $(OBJ_DIR)/%.o, $(SOURCES))
DEPENDS = $(wildcard $(OBJ_DIR)/*.d)

all: prebuild exe

prebuild: $(EXE_DIR) $(OBJ_DIR)

ifeq ($(OS), Windows_NT)
$(EXE_DIR):
	mkdir $(EXE_PREFIX)\$(EXE_SUFFIX)
$(OBJ_DIR):
	mkdir $(OBJ_PREFIX)\$(OBJ_SUFFIX)
else
$(EXE_DIR):
	mkdir -p $(EXE_DIR)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
endif

exe: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBRARIES)

ifneq ($(DEPENDS),)
include $(DEPENDS)
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(CXX) -c -o $@ $< $(MAKE_DEPS) $(WARNINGS) $(DEBUG) $(OPTIMIZE) $(CXX_STD) $(INCLUDES)

clean:
	$(RM) -v $(EXE) $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d

purge:
	$(RM) -r -v $(EXE_PREFIX) $(OBJ_PREFIX)
