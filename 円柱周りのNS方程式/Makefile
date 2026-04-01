CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra
TARGET = cylinder_ns_polar
SRC = cylinder_ns_polar.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

plot:
	gnuplot cylinder_ns_polar.gp

clean:
	rm -f $(TARGET)
