all: fila.o paciente.o testes.o registro.o
	gcc fila.o paciente.o testes.o registro.o -o testes -Wall -lm

verifica: fila.o paciente.o testes.o registro.o
	gcc -g -fsanitize=address fila.o paciente.o testes.o registro.o -o testes -std=c99 -Wall -lm

registro.o:
	gcc -c ../TAD_Registro/registro.c -o registro.o
fila.o:
	gcc -c fila.c -o fila.o 

paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c

testes.o:
	gcc -c testes.c -o testes.o 

make run:
	./testes
	
clean:
	rm *.o
	rm testes
