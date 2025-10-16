# Nombre del ejecutable
TARGET = hilos

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -pthread

# Archivos fuente
SRC = hilos.c

# Archivos objeto (los que genera el compilador)
OBJ = $(SRC:.c=.o)

# Regla principal (lo que se ejecuta si solo escribes "make")
all: $(TARGET)

# Cómo compilar el ejecutable
$(TARGET): $(OBJ)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Cómo generar los archivos objeto (.o) a partir del código fuente
%.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar el programa fácilmente
run: $(TARGET)
        ./$(TARGET)

# Regla para limpiar los archivos generados (muy útil)
clean:
        rm -f $(OBJ) $(TARGET)


