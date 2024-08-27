# Compilador y flags
CC = gcc
CFLAGS = -Wall -pthread -I./src/mutex

# Archivos fuente y objetos
SRCS = src/main.c src/barrera/barrera.c src/mutex/mutex.c src/read-write-lock/read-write.c src/semaforo/semaforo.c
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
TARGET = bin/main

# Regla para compilar todo
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
