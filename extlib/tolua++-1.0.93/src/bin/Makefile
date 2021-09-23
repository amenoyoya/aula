TARGET = tolua++
CC = gcc

CFLAGS = -O3
INCDIR = -I../../include
LIBDIR = -L../../../../lib/linux
LIBS = 

SRCS = tolua.c toluabind.c $(wildcard lua-5.1/*.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
