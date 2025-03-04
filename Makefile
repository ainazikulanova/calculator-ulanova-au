CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17
LDFLAGS = -lm

#
SRC_DIR = src
BUILD_DIR = build
UNIT_TESTS_DIR = tests/unit
INTEGRATION_TEST_DIR = tests/integration

#
APP_SRC = $(SRC_DIR)/main.c
APP_OBJ = $(BUILD_DIR)/main.o
APP_EXE = $(BUILD_DIR)/app.exe

#    unit-
TEST_SRC = $(UNIT_TESTS_DIR)/calculator_tests.cpp
TEST_OBJ = $(BUILD_DIR)/tests.o $(BUILD_DIR)/main_test.o
TEST_EXE = $(BUILD_DIR)/unit-tests.exe

# GoogleTest
GTEST_DIR = googletest
GTEST_BUILD = $(GTEST_DIR)/build
TEST_LDFLAGS = -L$(GTEST_BUILD) -lgtest -lgtest_main -lpthread

#
FORMAT_DIRS = $(SRC_DIR) $(UNIT_TESTS_DIR)
CLANG_FORMAT = clang-format

# Python virtualenv
VENV = venv
PYTHON = $(VENV)/bin/python
PIP = $(VENV)/bin/pip
INT_TESTS = $(INTEGRATION_TEST_DIR)/integration-tests.py

.PHONY: all clean run-int run-float run-unit-test format venv run-integration-tests gtest

#    unit-
all: $(APP_EXE) $(TEST_EXE)

# ---   ---
$(APP_EXE): $(APP_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# ---  GoogleTest ---
$(GTEST_DIR)/CMakeLists.txt:
	git clone https://github.com/google/googletest.git $(GTEST_DIR)

$(GTEST_BUILD): $(GTEST_DIR)/CMakeLists.txt
	mkdir -p $(GTEST_BUILD)
	cd $(GTEST_BUILD) && cmake .. && $(MAKE)

# ---  unit- ---
$(TEST_EXE): $(TEST_OBJ) | $(GTEST_BUILD)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LDFLAGS) $(LDFLAGS)

$(BUILD_DIR)/tests.o: $(UNIT_TESTS_DIR)/calculator_tests.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c -o $@ $<

$(BUILD_DIR)/main_test.o: $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -DUNIT_TEST -c -o $@ $<

# ---  ---
clean:
	rm -rf $(BUILD_DIR) $(VENV)

# ---   ---
run-int: $(APP_EXE)
	./$(APP_EXE)

run-float: $(APP_EXE)
	./$(APP_EXE) --float

# ---  unit- ---
run-unit-test: $(TEST_EXE)
	./$(TEST_EXE)

# ---   ---
format:
	@find $(FORMAT_DIRS) -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec $(CLANG_FORMAT) -i -style=file {} +

# ---   Python   pytest ---
venv:
	python3 -m venv $(VENV)
	$(PIP) install --upgrade pip
	$(PIP) install pytest

# ---    ---
run-integration-tests: venv $(APP_EXE)
	@APP_PATH=$(abspath $(APP_EXE)) $(PYTHON) -m pytest -v $(INTEGRATION_TEST_DIR)
