.PHONY: clean

BIN = sort

$(BIN): Sort.cc *.cc *.hh
	$(CXX) -o $@ Sort.cc Person.cc -Wall -Wextra

clean:
	rm -f $(BIN)

