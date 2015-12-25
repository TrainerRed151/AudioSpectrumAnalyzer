CC = gcc
CFLAGS = -Wall
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = run

USER_DEFINES=

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -lm -lncurses $(USER_DEFINES)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
