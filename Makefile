CC := gcc
CFLAGS := -Wall -Wextra
SRCS := hanoi.c
OBJS := $(SRCS:.c=.o)
TARGET = build

.PHONY: all clean

all: $(TARGET)

run:
	./$(TARGET)

%.c: %.o
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
