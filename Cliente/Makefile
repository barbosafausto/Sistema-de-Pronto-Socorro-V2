all: paciente.o fila.o registro.o cliente.o main.o
	gcc paciente.o fila.o registro.o cliente.o main.o -o main -Wall -lm

verifica: paciente.o registro.o fila.o cliente.o main.o
	gcc -g -fsanitize=address paciente.o registro.o fila.o cliente.o main.o -o main -std=c99 -Wall -lm
	
paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c
	
fila.o:
	gcc -c ../TAD_Fila/fila.c

registro.o:
	gcc -c ../TAD_Registro/registro.c

cliente.o:
	gcc -c cliente.c
	
main.o:
	gcc -c main.c

make run:
	./main
	
clean:
	rm *.o
	rm main
