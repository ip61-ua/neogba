CXX = clang++
CXXFLAGS = -std=c++26 -Iinclude -Isrc -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -march=native -fsanitize=address -fsanitize=undefined -MMD -MP -lspdlog
TEST_LDFLAGS = -lgtest -lgtest_main -pthread -lgmock

TARGET = build/neogba
TEST_TARGET = build/test_runner

SRCS = $(shell find src -name '*.cpp')
TEST_SRCS = $(shell find tests -name '*.cpp')

OBJS = $(patsubst %.cpp, build/obj/%.o, $(SRCS))
TEST_OBJS = $(patsubst %.cpp, build/obj/%.o, $(TEST_SRCS))
OBJS_NO_MAIN = $(filter-out build/obj/src/main.o, $(OBJS))

DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

.PHONY: all build run test clean docs serve

all: run

build: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(OBJS_NO_MAIN)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LDFLAGS) -g

build/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

docs:
	doxygen Doxyfile

serve: docs
	python -m http.server 8000 -d docs/html

clean:
	rm -rf build

-include $(DEPS)
