all: fila.o paciente.o teste.o
	gcc fila.o paciente.o teste.o -o main -Wall -lm

verifica: fila.o paciente.o testes.o 
	gcc -g -fsanitize=address fila.o paciente.o testes.o -o testes -std=c99 -Wall -lm

fila.o:
	gcc -c fila.c -o fila.o -Wall -lm

paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c

teste.o:
	gcc -c teste.c -o teste.o -Wall -lm

make run:
	./main
	
clean:
	rm *.o
	rm main
