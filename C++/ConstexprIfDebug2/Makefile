.PHONY: clean

all: release

BUILD_DIR = build
SRC_DIR = src
EXE = $(BUILD_DIR)/hello
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN_SRC = $(SRC_DIR)/main.c++
WARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wunreachable-code
CXX_STANDARD = -std=c++17

debug: WARNINGS += -Werror
debug: DEFINES = -DDEBUG
debug: OPTIMIZE = -Og -g
debug: $(BUILD_DIR) $(EXE)

release: DEFINES = -DNDEBUG
release: OPTIMIZE = -O3
release: $(BUILD_DIR) $(EXE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXE): $(MAIN_OBJ)
	$(CXX) -o $@ $^

$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) -c -o $@ $< $(CXX_STANDARD) $(WARNINGS) $(DEFINES) $(OPTIMIZE)

clean:
	$(RM) $(BUILD_DIR)/*
