.PHONY: clean

BINDIR = bin
EXECUTABLE = $(BINDIR)/hello
MAIN_CXX = main.cxx
CXX_STD = -std=c++17
WARNS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors

$(EXECUTABLE): $(MAIN_CXX)
	mkdir -p $(BINDIR)
	$(CXX) -o $@ $< $(CXX_STD) $(WARNS)

clean:
	rm -rf $(BINDIR)
