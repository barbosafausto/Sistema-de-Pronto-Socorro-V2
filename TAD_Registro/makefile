all: registro.o paciente.o testes.o
	gcc registro.o paciente.o testes.o -o testes -std=c99 -Wall -lm

verifica: registro.o paciente.o testes.o 
	gcc -g -fsanitize=address registro.o paciente.o testes.o -o testes -std=c99 -Wall -lm

registro.o:
	gcc -c ../TAD_Registro/registro.c

paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c

testes.o:
	gcc -c testes.c

make run:
	./testes

clean:
	rm registro.o
	rm paciente.o
	rm testes.o
	rm testes
