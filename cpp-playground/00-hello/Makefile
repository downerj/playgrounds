.PHONY: clean

EXECUTABLE := hello
EXECUTABLE_DIR := bin
OBJECT_DIR := obj
SOURCE_DIR := src
INCLUDE_DIR := src

WARNINGS := -Wall -Wextra -Werror -Wpedantic -pedantic-errors
OPTIMIZE := -Og
DEBUG := -g -DDEBUG
CXX_STANDARD := -std=c++17
LIBRARIES :=

SRC_MAIN := $(SOURCE_DIR)/main.cxx
OBJ_MAIN := $(OBJECT_DIR)/main.o
SRC_HELLO := $(SOURCE_DIR)/hello.cxx
INCL_HELLO := $(INCLUDE_DIR)/hello.hxx
OBJ_HELLO := $(OBJECT_DIR)/hello.o

define COMPILE =
$(CXX) -c -o $(1) $(2) $(WARNINGS) $(OPTIMIZE) $(DEBUG) $(CXX_STANDARD)
endef

all: $(EXECUTABLE_DIR) $(OBJECT_DIR) $(EXECUTABLE_DIR)/$(EXECUTABLE)

$(EXECUTABLE_DIR):
	mkdir $(EXECUTABLE_DIR)

$(OBJECT_DIR):
	mkdir $(OBJECT_DIR)

$(EXECUTABLE_DIR)/$(EXECUTABLE): $(OBJ_MAIN) $(OBJ_HELLO)
	$(CXX) -o $@ $^ $(LIBRARIES)

$(OBJ_MAIN): $(SRC_MAIN) $(INCL_HELLO)
	$(call COMPILE,$@,$<)

$(OBJ_HELLO): $(SRC_HELLO) $(INCL_HELLO)
	$(call COMPILE,$@,$<)

clean:
	rm -f $(OBJECT_DIR)/*.o $(EXECUTABLE_DIR)/*
