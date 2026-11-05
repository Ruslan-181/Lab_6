# Компілятор
CC = gcc

# Прапорці компілятора
CFLAGS = -Wall

# Назва програми
PROGRAM = lab5

# Компіляція програми
all: $(PROGRAM)

$(PROGRAM): Lab_5-.c Func.c Func.h
	$(CC) $(CFLAGS) Lab_5-.c Func.c -o $(PROGRAM) -lm

# Запуск програми
run: $(PROGRAM)
	./$(PROGRAM)

# Очищення створених файлів
clean:
	rm -f $(PROGRAM) output.txt data.bin

# Цілі, які не є файлами
.PHONY: all run clean