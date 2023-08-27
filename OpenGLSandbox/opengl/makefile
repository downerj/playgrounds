##############################################################################
# OS/CC CONDITIONAL RULES
##############################################################################
# test OS for OpenGL and $(PLATFORM)
ifeq ($(shell uname -s), Darwin)
    LIB_GL = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
 	PLATFORM = macos
# otherwise, it's Linux, Unix, etc.
# TODO: add more target platforms
else
    LIB_GL = -lGL
	PLATFORM = linux
endif

# test compiler for c++
ifeq ($(CC), clang)
	CPP = clang++
else
	CPP = g++
endif

##############################################################################
# LIBRARY VARIABLES
##############################################################################
# directories
LIB_OBJ_ROOT = libobj
LIB_SRC_ROOT = libsrc
LIB_ROOT = lib
LIB_NAME = utils
LIBRARY = lib$(LIB_NAME)
LIB_DIR = $(LIB_ROOT)/$(LIB_NAME)/$(PLATFORM)
LIB_HEAD_DIR = $(LIB_ROOT)/$(LIB_NAME)
LIB_SRC_DIR = $(LIB_SRC_ROOT)/$(LIB_NAME)

# compiler
LIB_CFLAGS = -fPIC -std=gnu11

# targets and includes
LIB_OBJS = \
	$(LIB_OBJ_ROOT)/utilinit.o \
	$(LIB_OBJ_ROOT)/utilinput.o \
	$(LIB_OBJ_ROOT)/utildraw.o \
	$(LIB_OBJ_ROOT)/utildebug.o \
	$(LIB_OBJ_ROOT)/utiltext.o
LIB_INCS = $(LIB_SRC_DIR)/utiltypes.h

##############################################################################
# LIBRARY DIRECTORY RULES
##############################################################################
cleanlibobj:
	rm -f $(LIB_OBJ_ROOT)/*.o

cleanlib:
	rm -f $(LIB_DIR)/*.a
	make cleanlibobj
	rm -f $(LIB_HEAD_DIR)/*.h

libdirs:
	if [ ! -d "$(LIB_DIR)" ]; then mkdir -p $(LIB_DIR); fi
	if [ ! -d "$(LIB_OBJ_ROOT)" ]; then mkdir -p $(LIB_OBJ_ROOT); fi
	if [ ! -d "$(LIB_HEAD_DIR)" ]; then mkdir -p $(LIB_HEAD_DIR); fi

##############################################################################
# LIBRARY RULES
##############################################################################
$(LIBRARY): $(LIB_OBJS)
	ar -ruv $(LIB_DIR)/$(LIBRARY).a $(LIB_OBJS)
	ranlib $(LIB_DIR)/$(LIBRARY).a
	cp $(LIB_SRC_DIR)/*.h $(LIB_HEAD_DIR)/

$(LIB_OBJ_ROOT)/%.o: $(LIB_SRC_DIR)/%.c $(LIB_SRC_DIR)/%.h $(LIB_INCS)
	$(CC) -c -o $@ $< $(LIB_CFLAGS) -I$(LIB_SRC_DIR)

##############################################################################
# USER OBJECT VARIABLES
##############################################################################
# directories
OBJ_ROOT = obj
BIN_ROOT = bin
BIN_DIR  = bin/$(PLATFORM)
SRC_ROOT = src

# compiler
STD_C = -std=gnu11
STD_CPP = -std=gnu++11
WARNS = -Wall -Wextra -Wno-unused-parameter
OPTIMIZE = -O2
CFLAGS_C = $(WARNS) $(STD_C) $(OPTIMIZE)
CFLAGS_CPP = $(WARNS) $(STD_CPP) $(OPTIMIZE)

# linker
LIB_MATH = -lm
# PKG_CFG_DIR = env PKG_CONFIG_PATH=./lib/GLFW/$(PLATFORM)
PKG_CFG_CFLAGS = `pkg-config --cflags glfw3`
PKG_CFG_LIB = `pkg-config --static --libs glfw3`
LIB_GLFW = $(PKG_CFG_CFLAGS) $(PKG_CFG_LIB)
LIB_UTILS = $(LIB_DIR)/$(LIBRARY).a
LFLAGS_C = $(LIB_GL) $(LIB_MATH) $(LIB_UTILS) $(LIB_GLFW)
LFLAGS_CPP = $(LFLAGS_C)

# extensions
CPP_EXT = cpp # cc, c++, cpp, C, cxx, etc.
HPP_EXT = hpp # hh, h++, hpp, H, hxx, etc.

##############################################################################
# USER OBJECT DIRECTORY RULES
##############################################################################
cleanuserobj:
	rm -f $(OBJ_ROOT)/*.*o

cleanuser:
	cleanuserobj
	rm -rf $(BIN_DIR)/*

userdirs:
	if [ ! -d "$(OBJ_ROOT)" ]; then mkdir -p $(OBJ_ROOT); fi
	if [ ! -d "$(BIN_DIR)" ]; then mkdir -p $(BIN_DIR); fi

##############################################################################
# USER OBJECT RULES
##############################################################################
$(OBJ_ROOT)/%.ho: $(SRC_ROOT)/%.c $(SRC_ROOT)/%.h
	$(CC) -c -o $@ $< $(CFLAGS_C) -I$(LIB_ROOT)

$(OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $< $(CFLAGS_C) -I$(LIB_ROOT)

$(OBJ_ROOT)/%.hoo: $(SRC_ROOT)/%.$(CPP_EXT) $(SRC_ROOT)/%.$(HPP_EXT)
	$(CPP) -c -o $@ $< $(CFLAGS_CPP) -I$(LIB_ROOT)

$(OBJ_ROOT)/%.oo: $(SRC_ROOT)/%.$(CPP_EXT)
	$(CPP) -c -o $@ $< $(CFLAGS_CPP) -I$(LIB_ROOT)

##############################################################################
# CUSTOM TARGETS
##############################################################################
OBJECTS1 = $(OBJ_ROOT)/one.o $(OBJ_ROOT)/one-player.ho
one: $(OBJECTS1)
	$(PKG_CFG_DIR) $(CC) -o $(BIN_DIR)/$@ $? $(LFLAGS_C)
	macos/appify one One
