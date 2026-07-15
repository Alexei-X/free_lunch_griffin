CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c11

TARGET = freelunch

SRCS = main.c \
       FiniteField.c \
       Griffin.c \
       Poly.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
