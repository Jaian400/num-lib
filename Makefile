CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS =

INCLUDE_DIR = include
SRC_DIR = src
TEST_SRC_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

APP_NAME = app

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_SRC_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS = $(patsubst $(TEST_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

TEST_BINS = $(patsubst $(TEST_SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

MAIN_TARGET = $(BIN_DIR)/$(APP_NAME)

DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

.PHONY: all clean directories tests run_tests

all: directories $(MAIN_TARGET) $(TEST_BINS)

tests: directories $(TEST_BINS)

directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(MAIN_TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_BINS): $(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

$(TEST_OBJS): $(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

-include $(DEPS)

run_tests: $(TEST_BINS)
	@echo "Running tests..."
	@for test_exe in $(TEST_BINS); do \
		echo "--- Running $$test_exe ---"; \
		./$$test_exe; \
		if [ $$? -ne 0 ]; then \
			echo "*** Test $$test_exe FAILED ***"; \
			exit 1; \
		fi; \
	done
	@echo "All tests passed."

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(APP_NAME)