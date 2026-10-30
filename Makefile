CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -I src

TARGET = system-health-check

SRC = src/main.c \
      src/metrics/memory.c \
      src/metrics/disk.c \
      src/display/display.c \
      src/display/charts.c \
      src/utils/format.c

OBJ = $(SRC:src/%.c=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run