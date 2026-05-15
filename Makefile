CC = gcc
CCFLAGS = -Wall -Wextra -Wanalyzer-allocation-size -Wanalyzer-deref-before-check -Wanalyzer-div-by-zero -Wanalyzer-double-fclose -Wanalyzer-double-free -Wanalyzer-exposure-through-output-file -Wanalyzer-exposure-through-uninit-copy -Wanalyzer-fd-access-mode-mismatch -Wanalyzer-fd-double-close -Wanalyzer-fd-leak -Wanalyzer-fd-phase-mismatch -Wanalyzer-fd-type-mismatch -Wanalyzer-fd-use-after-close -Wanalyzer-fd-use-without-check -Wanalyzer-file-leak -Wanalyzer-free-of-non-heap -Wanalyzer-imprecise-fp-arithmetic -Wanalyzer-infinite-loop -Wanalyzer-infinite-recursion -Wanalyzer-jump-through-null -Wanalyzer-malloc-leak -Wanalyzer-mismatching-deallocation -Wanalyzer-mkostemp-redundant-flags -Wanalyzer-mktemp-missing-placeholder -Wanalyzer-mktemp-of-string-literal -Wanalyzer-null-argument -Wanalyzer-null-dereference -Wanalyzer-out-of-bounds -Wanalyzer-overlapping-buffers -Wanalyzer-possible-null-argument -Wanalyzer-possible-null-dereference -Wanalyzer-putenv-of-auto-var -Wanalyzer-shift-count-negative -Wanalyzer-shift-count-overflow -Wanalyzer-stale-setjmp-buffer -Wanalyzer-tainted-allocation-size -Wanalyzer-tainted-array-index -Wanalyzer-tainted-assertion -Wanalyzer-tainted-divisor -Wanalyzer-tainted-offset -Wanalyzer-tainted-size -Wanalyzer-throw-of-unexpected-type -Wanalyzer-undefined-behavior-ptrdiff -Wanalyzer-undefined-behavior-strtok -Wanalyzer-unsafe-call-within-signal-handler -Wanalyzer-use-after-free -Wanalyzer-use-of-pointer-in-stale-stack-frame -Wanalyzer-use-of-uninitialized-value -Wanalyzer-va-arg-type-mismatch -Wanalyzer-va-list-exhausted -Wanalyzer-va-list-leak -Wanalyzer-va-list-use-after-va-end -Wanalyzer-write-to-const -Wanalyzer-write-to-string-literal -fanalyzer -Iinclude -Isrc -Iexternal/unity -DTEST -std=c2x
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
