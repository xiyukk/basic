# 每次编译的时候，在项目的根目录下运行make命令即可.

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++17 -D_POSIX_C_SOURCE=200809L

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

# Find all .cpp files and their corresponding .out files
CPP_FILES = $(shell find $(SRC_DIR) -name '*.cpp')
OUT_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%, $(CPP_FILES))

.PHONY: all clean

all: $(OUT_FILES)

# Rule for building .out files from .cpp files
$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -rf $(BUILD_DIR)

