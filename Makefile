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

SOURCES := $(wildcard $(SDIR)/*.cpp) $(wildcard $(TDIR)/*.cpp)
OBJECTS := $(patsubst %.cpp,$(ODIR)/%.o,$(notdir $(SOURCES)))

# This variable holds the test name passed from the command line.
# The ?= operator sets it only if it's not already set.
# This makes it default to empty if you just run "make run".
TEST ?=

# --- Makefile Rules ---

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to run the executable with a specific test
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
.PHONY: all run clean