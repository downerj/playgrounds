.PHONY: clean

#
# Build paths & parameters
#

SRC_DIR = .
INCL_DIR = .
OBJ_DIR = obj
EXE_DIR = bin
LIBRARIES =
CXX_STANDARD = -std=c++17
WARNINGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors
OPTIMIZE = -O3
DEBUGS =

#
# All
#

PERMUTE = permute
SHUFFLE = shuffle
REVERSE = reverse

all: $(PERMUTE) $(SHUFFLE) $(REVERSE)

#
# Includes
#

VECTOR_FN_HXX = $(INCL_DIR)/vector_fn.h++

#
# Permute
#

PERMUTE_EXE = $(EXE_DIR)/$(PERMUTE)
PERMUTE_CXX = $(SRC_DIR)/permute.c++
PERMUTE_OBJ = $(OBJ_DIR)/permute.o

$(PERMUTE): $(PERMUTE_EXE)
$(PERMUTE_EXE): $(PERMUTE_OBJ)
	mkdir -p "$(EXE_DIR)"
	$(CXX) -o "$@" "$^" $(LIBRARIES)

$(PERMUTE_OBJ): $(PERMUTE_CXX) $(VECTOR_FN_HXX)
	mkdir -p "$(OBJ_DIR)"
	$(CXX) -c -o "$@" "$<" $(CXX_STANDARD) $(WARNINGS) $(DEBUGS) $(OPTIMIZE)

#
# Shuffle
#

SHUFFLE_EXE = $(EXE_DIR)/$(SHUFFLE)
SHUFFLE_CXX = $(SRC_DIR)/shuffle.c++
SHUFFLE_OBJ = $(OBJ_DIR)/shuffle.o

$(SHUFFLE): $(SHUFFLE_EXE)
$(SHUFFLE_EXE): $(SHUFFLE_OBJ)
	mkdir -p "$(EXE_DIR)"
	$(CXX) -o "$@" "$^" $(LIBRARIES)

$(SHUFFLE_OBJ): $(SHUFFLE_CXX) $(VECTOR_FN_HXX)
	mkdir -p "$(OBJ_DIR)"
	$(CXX) -c -o "$@" "$<" $(CXX_STANDARD) $(WARNINGS) $(DEBUGS) $(OPTIMIZE)

#
# Reverse
#

REVERSE_EXE = $(EXE_DIR)/$(REVERSE)
REVERSE_CXX = $(SRC_DIR)/reverse.c++
REVERSE_OBJ = $(OBJ_DIR)/reverse.o

$(REVERSE): $(REVERSE_EXE)
$(REVERSE_EXE): $(REVERSE_OBJ)
	mkdir -p "$(EXE_DIR)"
	$(CXX) -o "$@" "$^" $(LIBRARIES)

$(REVERSE_OBJ): $(REVERSE_CXX) $(VECTOR_FN_HXX)
	mkdir -p "$(OBJ_DIR)"
	$(CXX) -c -o "$@" "$<" $(CXX_STANDARD) $(WARNINGS) $(DEBUGS) $(OPTIMIZE)

#
# Clean
#

clean:
	rm -rf "$(OBJ_DIR)" "$(EXE_DIR)"
