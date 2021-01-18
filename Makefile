CC = g++
CFLAGS = -Wall
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = run

USER_DEFINES=

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -lm -lncurses $(USER_DEFINES)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
