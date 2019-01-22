CC=gcc
FLAGS=-Wall 
EXEC=projetTrafic
SRC= 	main.c \
	dangerMode.c \
	dangerMode.h \
	trafic.c \
	trafic.h \
	menu.c \
	menu.h
OBJ=$(SRC:.c=.o)

all: $(EXEC)
	./projetTrafic

projetTrafic: $(OBJ)
	$(CC) -o $@ $^ 


%.o: %.c
	$(CC) -o $@ -c $^ $(FLAGS) 

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
