# 每次编译的时候，在项目的根目录下运行make命令即可.

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

# Find all .c files and their corresponding .out files
C_FILES = $(shell find $(SRC_DIR) -name '*.c')
OUT_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%, $(C_FILES))

.PHONY: all clean

all: $(OUT_FILES)

# Rule for building .out files from .c files
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -rf $(BUILD_DIR)