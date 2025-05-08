.PHONY: default

ARDUINO = /usr/bin/env arduino
BOARD = arduino:avr:leonardo
PORT = /dev/ttyACM0
PREF_WARNING_LEVEL = --pref compiler.warning_level=all

default: verify

verify: Ship.ino *.h *.cpp
	$(ARDUINO) --board $(BOARD) --verify $(PREF_WARNING_LEVEL) $<

upload: Ship.ino *.h *.cpp
	$(ARDUINO) --board $(BOARD) --port $(PORT) --upload $(PREF_WARNING_LEVEL) $<
