CXX = clang++
CXXFLAGS = -std=c++26 -Iinclude -Isrc -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -march=native -fsanitize=address -fsanitize=undefined 

TEST_LDFLAGS = -lgtest -lgtest_main -pthread -lgmock

TARGET = build/neogba
TEST_TARGET = build/test_runner

SRCS = $(shell find src -name '*.cpp')
TEST_SRCS = $(shell find tests -name '*.cpp')
SRCS_NO_MAIN = $(filter-out src/main.cpp, $(SRCS))

.PHONY: all build run test clean docs

all: run

build: $(SRCS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)

test: $(TEST_SRCS) $(SRCS_NO_MAIN)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) $(SRCS_NO_MAIN) $(TEST_LDFLAGS) -g
	./$(TEST_TARGET)

docs:
	doxygen Doxyfile

serve: docs
	python -m http.server 8000 -d docs/html

clean:
	rm -rf build/*
