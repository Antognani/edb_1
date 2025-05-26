CC=gcc
CFLAGS=-Wall -Wextra -g -std=c99 

# Nome do executável final
TARGET=sistemaRestaurante

# Arquivos fonte .c
SOURCES=main.c lista_salao.c fila_cozinha.c

# Arquivos objeto .o (gerados a partir dos .c)
OBJECTS=$(SOURCES:.c=.o)

# Regra padrão: compilar tudo
all: $(TARGET)

# Regra para linkar e criar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos compilados e o executável
clean:
	rm -f $(OBJECTS) $(TARGET) *.exe 

# Evita que o make confunda os alvos 'all' e 'clean' com nomes de arquivos reais
.PHONY: all clean