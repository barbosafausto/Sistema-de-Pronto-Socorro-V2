all: fila.o teste.o
	gcc fila.o teste.o -o main -Wall -lm
	rm *.o

fila.o:
	gcc -c fila.c -o fila.o -Wall -lm

teste.o:
	gcc -c teste.c -o teste.o -Wall -lm

clean:
	rm *.o
	rm main