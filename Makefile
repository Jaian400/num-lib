CXX        := g++
# CXXFLAGS   := -std=c++17 -Wall -Wextra -g
CXXFLAGS   := -std=c++17 -w
LDFLAGS    :=

IDIR       := include
SDIR       := src
TDIR       := tests
ODIR       := obj
BDIR       := bin

TARGET     := run_tests
EXECUTABLE := $(BDIR)/$(TARGET)

INCLUDES   := -I$(IDIR)

VPATH := $(SDIR):$(TDIR)

# --- Define Source and Object files ---

# NEW: Sources and Objects for the LIBRARY ONLY
LIB_SOURCES := $(wildcard $(SDIR)/*.cpp)
LIB_OBJECTS := $(patsubst %.cpp,$(ODIR)/%.o,$(notdir $(LIB_SOURCES)))

# Sources and Objects for the FULL TEST EXECUTABLE (Library + Tests)
SOURCES := $(LIB_SOURCES) $(wildcard $(TDIR)/*.cpp)
OBJECTS := $(patsubst %.cpp,$(ODIR)/%.o,$(notdir $(SOURCES)))


# This variable holds the test name passed from the command line.
# The ?= operator sets it only if it's not already set.
# This makes it default to empty if you just run "make run".
TEST ?=

# --- Makefile Rules ---

# Default target: build the executable
all: $(EXECUTABLE)

# Target to compile only the library object files
library: $(LIB_OBJECTS)
	@echo "Library object files are compiled in $(ODIR)/"

# Pass the test name using: make run TEST=<test_name>
run: all
	@echo "--- Running test: $(TEST) ---"
	./$(EXECUTABLE) $(TEST)

# Rule to link all object files into the final executable
$(EXECUTABLE): $(OBJECTS) | $(BDIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule to compile .cpp files into .o object files
$(ODIR)/%.o: %.cpp | $(ODIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the bin and obj directories
$(BDIR) $(ODIR):
	mkdir -p $@

# Rule to clean up generated files
clean:
	@echo "Cleaning up..."
	rm -rf $(ODIR) $(BDIR)

# Declare phony targets
# NEW: Added 'library' to the phony list
.PHONY: all run clean library