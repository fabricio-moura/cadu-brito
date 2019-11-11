all: projeto

projeto: main.o checagens.o primitivas.o
	gcc -o projeto main.o checagens.o primitivas.o

main.o: main.c checagens.h tipos.h primitivas.h
	gcc -o main.o main.c -c -Wall -Werror

checagens.o: checagens.c checagens.h primitivas.h
	gcc -o checagens.o checagens.c -c -Wall -Werror

primitivas.o: primitivas.c primitivas.h checagens.h
	gcc -o primitivas.o primitivas.c -c -Wall -Werror

clean:
	rm -rf *.o *~ all
