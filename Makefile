SHELL := /bin/sh

CXX := g++
STD := -std=c++17
INCLUDE := -Iinclude
COMMON_FLAGS := -O2 -Wall -Wextra
CXXFLAGS := $(STD) $(COMMON_FLAGS) $(INCLUDE) -MMD -MP

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
TARGET := $(BIN_DIR)/hero

# Recursively find source files (works with MSYS/MinGW). Fallback to non-recursive if needed.
SRCS := $(shell find src -name '*.cpp' 2>/dev/null)
ifeq ($(strip $(SRCS)),)
SRCS := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
endif

# Add main.cpp at root
SRCS += main.cpp

# map src/.../*.cpp -> build/obj/.../*.o, main.cpp -> build/obj/main.o
OBJS := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(filter src/%,$(SRCS)))
OBJS += $(OBJ_DIR)/main.o
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

# link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# compile (create parent dir if needed)
$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# compile main.cpp at root
$(OBJ_DIR)/main.o: main.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ensure bin dir exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# include generated dependency files (if any)
-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) hero

run: $(TARGET)
	$(TARGET)