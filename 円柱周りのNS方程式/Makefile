CC = cc
CFLAGS = -O3 -std=c11 -Wall -Wextra -pedantic
TARGET = cylinder_ns
SRC = cylinder_ns.c

.PHONY: all run plot clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

plot:
	gnuplot plot_cylinder.gnuplot

clean:
	rm -f $(TARGET) cylinder_field_final.dat cylinder_surface.dat cylinder_grid.dat cylinder_grid_wake.dat cylinder_wake_map.dat cylinder_history.dat cylinder_overview.png cylinder_wake_contours.dat
