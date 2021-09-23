TARGET = libtolua++.a
CC = gcc
AR = ar

CFLAGS = -O3
ARFLAGS = rcs
INCDIR = -I../bin/lua-5.1
LIBDIR = 
LIBS = 

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $< $(INCDIR) $(LIBDIR) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
