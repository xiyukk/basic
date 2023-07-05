.PHONY: clean
# 最初始的形式
# simple: main.o foo.o
# 	gcc -o simple main.o foo.o
# main.o: main.c
# 	gcc -o main.o -c main.c
# foo.o: foo.c
# 	gcc -o foo.o -c foo.c
# clean:
# 	rm simple main.o foo.o


# 变量形式
# CC = gcc
# RM = rm
# EXE = simple
# OBJS = main.o foo.o

# $(EXE): $(OBJS)
# 	$(CC) -o $(EXE) $(OBJS)
# main.o: main.c
# 	$(CC) -o main.o -c main.c
# foo.o: foo.c
# 	$(CC) -o foo.o -c foo.c
# clean:
# 	$(RM) $(EXE) $(OBJS)

# 三种特殊变量形式：$@ $^ $>
# $(EXE): $(OBJS)
# 	$(CC) -o $@ $^
# main.o: main.c
# 	$(CC) -o $@ -c $^
# foo.o: foo.c
# 	$(CC) -o $@ -c $^
# clean:
# 	$(RM) $(EXE) $(OBJS)


# 模式形式
# $(EXE): $(OBJS)
# 	$(CC) -o $@ $^
# %.0: %.c
# 	$(CC) -o $@ -c $^
# clean:
# 	$(RM) $(EXE) $(OBJS)


# 函数形式
CC = gcc
RM = rm
EXE = simple

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) -o $@ -c $^
clean:
	$(RM) $(EXE) $(OBJS)




