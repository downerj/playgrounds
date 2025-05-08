.PHONY: clean

EXE_DIR = bin
SRC_DIR = .
INC_DIR = .
OBJ_DIR = obj
EXE = $(EXE_DIR)/example
MAIN_CXX = $(SRC_DIR)/main.cxx
MAIN_OBJ = $(OBJ_DIR)/main.o

$(EXE): $(MAIN_OBJ)
	mkdir -p $(OBJ_DIR) $(EXE_DIR)
	$(CXX) -o $@ $^

$(MAIN_OBJ): $(MAIN_CXX)
	$(CXX) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

$(EXE_DIR):
	mkdir -p $@

clean:
	rm -f $(EXE_DIR)/* $(OBJ_DIR)/*
