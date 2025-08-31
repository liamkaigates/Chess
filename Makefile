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

# Default goal
.DEFAULT_GOAL := all

# Define the compiler
CXX = g++

# Split compile vs link flags: avoid passing linker flags at compile time
# Compiler flags (no linker libs here)
CXXFLAGS = -I$(IDIR) -Wall -Wextra -g -std=c++20 -Wunused-parameter

# Linker flags and libraries
LDLIBS_APP = -lSDL2 -lSDL2_ttf -lm

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
XXLIBS = $(LIBS) -lSDL2 -lSDL2_ttf -lgtest -lgtest_main -pthread

# Define the dependencies with their paths
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Define the object files with their paths
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
MOBJ = $(patsubst %,$(ODIR)/%,$(_MOBJ))
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ)) 

# Ensure object directory exists
$(ODIR):
	mkdir -p $(ODIR)

# Rule to compile source files into object files
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule to compile test file explicitly (avoid duplicate pattern rules)
$(ODIR)/test.o: $(TDIR)/test.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule to build all targets
all: $(APPBIN) $(TESTBIN)

# Rule to build the main application
$(APPBIN): $(OBJ) $(MOBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS_APP)

# Rule to build the test application
$(TESTBIN): $(TOBJ) $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(XXLIBS) $(LDIRS)

# Rule to clean the project
.PHONY: all clean
clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
	rm -f $(APPBIN) $(TESTBIN)
