CC = gcc
CCFLAGS = -Wall -Wextra -Iinclude -Isrc -Iexternal/unity -DTEST
TEST_LDFLAGS = 

TARGET = build/neogba
TEST_TARGET = build/test_runner

SRCS = $(shell find src -name '*.c')
TEST_SRCS = $(shell find tests -name '*.c')
SRCS_NO_MAIN = $(filter-out src/main.c, $(SRCS))
UNITY_SRC = external/unity/unity.c

UNITY_URL = https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src

.PHONY: all build run test clean

all: run

external/unity:
	@mkdir -p external/unity
	@if [ ! -f $(UNITY_SRC) ]; then \
		curl -s -o external/unity/unity.c $(UNITY_URL)/unity.c; \
		curl -s -o external/unity/unity.h $(UNITY_URL)/unity.h; \
		curl -s -o external/unity/unity_internals.h $(UNITY_URL)/unity_internals.h; \
	fi

build: $(SRCS)
	@mkdir -p build
	$(CC) $(CCFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)

test: $(TEST_SRCS) $(SRCS_NO_MAIN)
	@mkdir -p build
	$(CC) $(CCFLAGS) -o $(TEST_TARGET) $(UNITY_SRC) $(TEST_SRCS) $(SRCS_NO_MAIN) $(TEST_LDFLAGS)
	./$(TEST_TARGET)

clean:
	rm -rf build/*
