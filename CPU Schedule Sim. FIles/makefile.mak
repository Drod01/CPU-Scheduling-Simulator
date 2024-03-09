CC = gcc
CFLAGS = -g -fopenmp -lm -lrt -std=c99 -Wall -D_POSIX_C_SOURCE=199309L -pthread
LDLIBS = -lpthread

TARGET = assign3

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) 

clean:
	rm -f $(TARGET)

run: 
	./$(TARGET)