# Definición del compilador y las banderas de compilación
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nombre del ejecutable
TARGET = myprogram

# Archivos fuente
SRCS = CityDefender.c Cartas.c Tablero.c

# Archivos objeto generados
OBJS = $(SRCS:.c=.o)

# Regla por defecto
all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos .c en archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS)

# Regla para limpiar todos los archivos generados, incluyendo los temporales
cleanall: clean
	rm -f *~

# Regla para mostrar la ayuda
help:
	@echo "Opciones disponibles:"
	@echo "  all     - Compila el programa"
	@echo "  clean   - Elimina archivos generados"
	@echo "  cleanall - Elimina archivos generados y temporales"
	@echo "  help    - Muestra esta ayuda"