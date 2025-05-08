.PHONY: clean

EXE_DIR = bin
SRC_DIR = src
INC_DIR = src
TARGET ?=
WARNINGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors
CXX_STD = -std=c++17

VISITORS_EXE = $(EXE_DIR)/visitors
VISITORS_SRC = $(SRC_DIR)/visitors.cxx

$(VISITORS_EXE): $(VISITORS_SRC) $(EXE_DIR)
	$(CXX) -o $@ $< $(WARNINGS) $(CXX_STD)

$(EXE_DIR):
	mkdir -p $(EXE_DIR)

clean:
	rm -rf $(EXE_DIR)
