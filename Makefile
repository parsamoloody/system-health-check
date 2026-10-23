CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
TARGET = system-metrics
OBJS = main.o metrics.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c metrics.h
	$(CC) $(CFLAGS) -c main.c -o main.o

metrics.o: metrics.c metrics.h
	$(CC) $(CFLAGS) -c metrics.c -o metrics.o

clean:
	rm -f $(OBJS) $(TARGET)