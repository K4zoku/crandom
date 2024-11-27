CC := cc
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
    DIST := $(DIST)/win
    LIB_EXT := dll
    OBJECTS := $(filter-out $(OBJ)/%.posix.o, $(OBJECTS))
    override LDFLAGS += -Wl,--out-implib,$(LIB)/$(NAME).lib
    TEST_LDFLAGS += -static
else
    DIST := $(DIST)/unix
    LIB_EXT := so
    OBJECTS := $(filter-out $(OBJ)/%.win32.o, $(OBJECTS))
    override CFLAGS += -fPIC
    TEST_LDFLAGS += -Wl,-rpath=$(LIB)
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
	$(foreach test, $(TESTS_BIN), $(test);)
endif

memcheck: compile $(TESTS_BIN)
	$(foreach test, $(TESTS_BIN), valgrind $(test);)

clean_tests:
	rm -rf $(BIN)/test*

$(BIN)/%: $(TEST)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(TEST_LDFLAGS)
