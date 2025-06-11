# Compiler and flags
CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -Wextra -g
# CXXFLAGS   := -std=c++17 -w -g #no warnings
LDFLAGS    :=

# Directories
IDIR       := include
SDIR       := src
TDIR       := tests
ODIR       := obj
BDIR       := bin

# Target executable name
TARGET     := run_tests
EXECUTABLE := $(BDIR)/$(TARGET)

# Include path flag
INCLUDES   := -I$(IDIR)

# VPATH tells 'make' where to look for source files
VPATH := $(SDIR):$(TDIR)

# Automatically find all .cpp source files in the source and tests directories
SOURCES := $(wildcard $(SDIR)/*.cpp) $(wildcard $(TDIR)/*.cpp)

# Generate corresponding object file names, placing them in the ODIR directory
OBJECTS := $(patsubst %.cpp,$(ODIR)/%.o,$(notdir $(SOURCES)))

# --- Makefile Rules ---

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to run the executable
run: all
	@echo "--- Running executable ---"
	./$(EXECUTABLE)
	@echo "--------------------------"

# Rule to link all object files into the final executable
$(EXECUTABLE): $(OBJECTS) | $(BDIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule to compile .cpp files into .o object files
# It finds sources via VPATH and places objects in ODIR.
$(ODIR)/%.o: %.cpp | $(ODIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the bin and obj directories if they don't exist
# This is an "order-only prerequisite"
$(BDIR) $(ODIR):
	mkdir -p $@

# Rule to clean up generated files
clean:
	@echo "Cleaning up..."
	rm -rf $(ODIR) $(BDIR)

# Declare phony targets that are not actual files
.PHONY: all run clean