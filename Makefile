CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = CityDefender

SRCS = CityDefender.c Cartas.c Tablero.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

cleanall: clean
	rm -f *~

help:
	@echo "Opciones disponibles:"
	@echo "  all     - Compila el programa"
	@echo "  clean   - Elimina archivos generados"
	@echo "  cleanall - Elimina archivos generados y temporales"
	@echo "  help    - Muestra esta ayuda"