.PHONY: all
# all: first second third
# 	@echo "\$$@ = $@"
# 	@echo "$$^ = $^"
# 	@echo "$$< = $<"
# first second third:

# override 在命令行赋值的变量不会覆盖Makefile文件中的变量
foo = a.o b.o c.o
override bar := $(foo:.o=.c)

# addprefix函数：是用来在给字符串中的每个子串前加上一个前缀
without_dir = foo.c bar.c main.o
with_dir = $(addprefix user/,$(without_dir))

# filter 函数用于从一个字符串中，根据模式得到满足模式的字符串
sources = foo.c bar.c baz.s ugh.h
sources := $(filter %.c %.s, $(sources))

# filter-out 函数用于从一个字符串中根据模式滤除一部分字符串
objects = main1.o foo.o main2.o bar.o
result = $(filter-out main%.o, $(objects))

# patsubst 函数是用来进行字符串替换的，其形式是：
# $(patsubst pattern, replacement, text)
mixed = foo.c bar.c main.o
objects := $(patsubst %.c, %.o, $(mixed))

# strip 函数用于去除变量中的多余的空格，其形式是：
# $(strip string)
original = foo.c 			bar.c
stripped := $(strip $(original))


# wildcard 是通配符函数，通过它可以得到我们所需的文件，这个函数如果我们在 Windows 或是
# Linux 命令行中的“*”。其形式是：
# $(wildcard pattern)
SRCS = $(wildcard *.c)


all:
#	@echo "bar = $(bar)"
#	@echo "with_dir = $(with_dir)"
#	@echo "sources = $(sources)"
#	@echo "result = $(result)"
#	@echo "objects = $(objects)"
#	@echo "original = $(original)"
#	@echo "stripped = $(stripped)"
	@echo "SRCS = $(SRCS)"