# Nombre del compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall

# Directorios
SRCDIR = src
BINDIR = bin
OBJDIR = build

# Archivos fuente
SRCS = $(wildcard $(SRCDIR)/*.c)

# Archivos objeto
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Nombre del programa final
TARGET = $(BINDIR)/hola_mundo

# Objetivo por defecto
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar archivos .c a archivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Regla para limpiar archivos generados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)