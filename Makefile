override CFLAGS += -O2 -Wall -Wextra -std=c99 -pedantic
override LDFLAGS += -lm

NAME = crandom

SRC = src
TEST = test
INC = -I$(SRC)
DIST := dist
OBJ = $(DIST)/obj
LIB = $(DIST)/lib
BIN = $(DIST)/bin
COLORED_OUTPUT = 1

# Function to recursively find files matching a pattern
rwildcard = $(foreach d,$(wildcard $(1)/*),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Find source files and map to object files
SOURCES = $(call rwildcard,$(SRC),*.c)
OBJECTS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))
TESTS = $(call rwildcard,$(TEST),*.c)
TESTS_BIN = $(patsubst $(TEST)/%.c,$(BIN)/%,$(TESTS))
TEST_LDFLAGS = -L$(LIB) -l$(NAME)

# Platform-specific adjustments

ifeq ($(OS),Windows_NT)
    override CFLAGS += -D WIN32
    DIST := $(DIST)/win
    LIB_EXT := dll
    OBJECTS := $(filter-out $(OBJ)/%.posix.o, $(OBJECTS))
    override LDFLAGS += -Wl,--out-implib,$(LIB)/$(NAME).lib
    TEST_LDFLAGS += -static
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        override CFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            override CFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            override CFLAGS += -D IA32
        endif
    endif
else
	DIST := $(DIST)/unix
	LIB_EXT := so
	OBJECTS := $(filter-out $(OBJ)/%.win32.o, $(OBJECTS))
	override CFLAGS += -fPIC
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        override CFLAGS += -D LINUX
        TEST_LDFLAGS += -Wl,-rpath=$(LIB)
    endif
    ifeq ($(UNAME_S),Darwin)
        override CFLAGS += -D OSX
        TEST_LDFLAGS += -Wl,-install_name=$(LIB)
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        override CFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        override CFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        override CFLAGS += -D ARM
    endif
endif

ifeq ($(COLORED_OUTPUT),1)
	override CFLAGS += -DCOLORED_OUTPUT=1
endif

# check if build for debug
ifeq ($(DEBUG),1)
	override CFLAGS += -g
endif

# Default target
default: clean compile

# Cleaning
clean:
	rm -rf $(OBJ) $(LIB) $(BIN)

# Compilation
compile: $(OBJECTS)
	@mkdir -p $(LIB)
	$(CC) $(INC) $(CFLAGS) $(OBJECTS) -o $(LIB)/lib$(NAME).$(LIB_EXT) $(LDFLAGS) -shared

# Object file compilation
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

docs:
	doxygen doxygen.conf

clean_docs:
	rm -rf docs

test: compile $(TESTS_BIN)
ifeq ($(OS),Windows_NT)
	@cp $(LIB)/lib$(NAME).$(LIB_EXT) $(BIN)
	$(foreach test, $(TESTS_BIN), $(test).exe;)
else
ifeq ($(UNAME_S),Darwin)
    @cp $(LIB)/lib$(NAME).$(LIB_EXT) $(BIN)
endif
	$(foreach test, $(TESTS_BIN), $(test);)
endif

memcheck: compile $(TESTS_BIN)
	$(foreach test, $(TESTS_BIN), valgrind $(test);)

clean_tests:
	rm -rf $(BIN)/test*

$(BIN)/%: $(TEST)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(TEST_LDFLAGS)
