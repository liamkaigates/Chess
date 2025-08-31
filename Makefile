# Define the dependencies
_DEPS = bitboard.h game.h move.h engine.h sdl_helper.h

# Define the object files
_OBJ = engine.o game.o sdl_helper.o pawn.o rook.o knight.o bishop.o queen.o king.o move.o board.o ai.o
_MOBJ = main.o
_TOBJ = test.o

# Define the binary names
APPBIN = chess_app
TESTBIN = chess_test

# Define the include directory
IDIR = include

# Define the compiler
CC = g++

# Define the compiler flags
CFLAGS = -I$(IDIR) -Wall -Wextra -g -lSDL2 -lSDL2_ttf -std=c++20 -Wunused-parameter

# Define the object directory
ODIR = obj

# Define the source directory
SDIR = src

# Define the library directory
LDIR = lib

# Define the test directory
TDIR = test

# Define the libraries
LIBS = -lm
# GoogleTest library path (auto-detected when possible)
LDIRS :=
# Prefer Homebrew Cellar on macOS if present
ifneq ($(wildcard /usr/local/Cellar/googletest/*/lib),)
  GTEST_CELLAR:=$(lastword $(sort $(wildcard /usr/local/Cellar/googletest/*)))
  LDIRS += -L$(GTEST_CELLAR)/lib
endif
ifneq ($(wildcard /opt/homebrew/Cellar/googletest/*/lib),)
  GTEST_CELLAR:=$(lastword $(sort $(wildcard /opt/homebrew/Cellar/googletest/*)))
  LDIRS += -L$(GTEST_CELLAR)/lib
endif

# Link libraries (include pthread for gtest)
XXLIBS = $(LIBS) -lgtest -lgtest_main -pthread

# Define the dependencies with their paths
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Define the object files with their paths
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
MOBJ = $(patsubst %,$(ODIR)/%,$(_MOBJ))
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ)) 

# Rule to compile source files into object files
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to compile test files into object files
$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to build all targets
all: $(APPBIN) $(TESTBIN)

# Rule to build the main application
$(APPBIN): $(OBJ) $(MOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Rule to build the test application
$(TESTBIN): $(TOBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(XXLIBS) $(LDIRS)

# Rule to clean the project
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
	rm -f $(APPBIN) $(TESTBIN)
