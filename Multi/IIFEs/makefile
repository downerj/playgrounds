.PHONY: clean

BINARY = iife
CFLAGS = -Wall -Wextra
LFLAGS = 

$(BINARY): iife.oo
	$(CXX) -o $@ $^ $(LFLAGS)

iife.oo: iife.cc
	$(CXX) -c -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BINARY)