all: paciente.o procedimento.o fila.o registro.o historico.o cliente.o main.o
	gcc paciente.o procedimento.o fila.o registro.o historico.o cliente.o main.o -o main -Wall -lm

verifica: paciente.o procedimento.o registro.o fila.o historico.o cliente.o main.o
	gcc -g -fsanitize=address paciente.o procedimento.o registro.o fila.o historico.o cliente.o main.o -o main -std=c99 -Wall -lm
	
paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c

procedimento.o:
	gcc -c ../TAD_Procedimento/procedimento.c
	
fila.o:
	gcc -c ../TAD_Fila/fila.c

registro.o:
	gcc -c ../TAD_Registro/registro.c

historico.o:
	gcc -c ../TAD_Historico/historico.c

cliente.o:
	gcc -c cliente.c
	
main.o:
	gcc -c main.c

make run:
	./main
	
clean:
	rm *.o
	rm main
