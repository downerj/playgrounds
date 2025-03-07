.PHONY: clean

BINARY = abstract
CFLAGS = -Wall -Wextra
#LFLAGS =

$(BINARY): abstract.oo
	$(CXX) -o $@ $^ $(LFLAGS)

abstract.oo: abstract.cc
	$(CXX) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINARY)
