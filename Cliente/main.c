#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#define TAM_MAX 101

void menu(){
	puts("=-=-=-=-=-HOSPITAL-=-=-=-=-=\n\n");
	puts("Operações: \n");
	puts(" [1] Registrar Paciente\n");
	puts(" [2] Remover Paciente\n");
	puts(" [3] Listar Pacientes\n");
	puts(" [4] Buscar Paciente por ID\n");
	puts(" [5] Mostrar Fila de Espera\n");
	puts(" [6] Dar Alta ao Paciente\n");
	puts(" [7] Adicionar Procedimento\n");
	puts(" [8] Desfazer Procedimento\n");
	puts(" [9] Mostrar Histórico de Paciente\n");
	puts(" [10] Sair\n");
	puts("Selecione uma: ");
}

void urgencias() {

	puts("=-=-=-=-=-URGÊNCIAS-=-=-=-=-=\n");
  	puts("Escolha a urgência deste paciente:\n") ;

	puts(" [1] Emergência: caso gravíssimo com risco de morte.\n");
	puts(" [2] Muito urgente: grave e risco de evoluir para morte.\n");
	puts(" [3] Urgente: gravidade moderada e necessidade de atendimento médico, sem risco imediato.\n");
	puts(" [4] Pouco Urgente: poderia ser atendido numa Unidade Básica.\n");
	puts(" [5] Não Urgência: risco algum (resfriados, espinho no pé, etc.)\n");
}

int main() {
	int op = 0, id;
	char nome[TAM_MAX], proced[TAM_MAX], urgencia = '0';

	REGISTRO *r;
	FILA *f;
	PACIENTE *p;
	inicializar(&r, &f);

	while(1){
		system("clear");
		menu();
		
		if (!scanf(" %d", &op)) op = 0;
		printf("\n");

		switch(op){

			case 1:
				puts("--- Registro de Paciente ---\n");
				puts("ID do novo paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				puts("Nome do paciente: ");
				scanf(" %100[^\n]", nome);

				urgencias();
				while (true) {

				  scanf(" %c", &urgencia);

				  if (urgencia < '1' || urgencia > '5') 
					printf("Por favor, escolha uma urgência válida.\n");

				  else break;
				}

				int_8 feedback = registrar_paciente(r, f, id, nome, urgencia);

				printf("--- Resultado do Registro ---\n");
				if (feedback == NAO_ESTA) printf("Registro bem-sucedido.\nO paciente foi registrado e colocado na fila.\n");

				else if (feedback == ESTA_REGISTRO) 
				  printf("O paciente já estava registrado.\nInserção na fila bem sucedida.");

				else if (feedback == ESTA_FILA)
				  printf("Não há necessidade de registro.\nO paciente está registrado e também está na fila.\n");

				else if (feedback == REPETIDO)
				  printf("Erro ao registrar paciente.\nJá existe um paciente com ID %d.\n", id);

				break;



        

			case 2:
				puts("--- Remover Paciente ---\n");
				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				p = remover_paciente(r, id);

				if (!p) {
				  
				  printf("Falha ao remover o paciente de ID %d\n", id);
				  printf("Por favor, verifique se ele está registrado ou se ele está na fila.\n");
				}

				else {
				  printf("--- Paciente Removido com Sucesso ---\n");
				  printf("%06d | %s\n", paciente_get_id(p), paciente_get_nome(p)); //Imprime os números de forma alinhada

				}

				paciente_apagar(&p); //Nãoooo pode esquecer
				break;




			case 3:
				puts("--- Lista de Pacientes ---\n");

  		        registro_listar(r);
				break;




			case 4:
				puts("--- Buscar Paciente ---\n");
				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				p = buscar_paciente_por_ID(r, id);

				if (p == NULL){
				printf("--- Nenhum paciente com o ID %d foi encontrado no registro. ---\n", id);
				}
				else {
				printf("Paciente encontrado.\n");
				printf("%06d | %s\n", paciente_get_id(p), paciente_get_nome(p)); //Imprime os números de forma alinhada
				}
				
				break;
			
        


			case 5:
				puts("--- Mostrar Fila de Espera ---\n");

      			mostrar_fila_de_espera(&f);

				break;






			case 6:
				puts("--- Dar Alta ao Paciente ---\n");

				p = dar_alta_ao_paciente(f);

				if (!p) printf("Não foi possível dar alta a um paciente, pois a fila está vazia.\n");
				else {
				printf("O seguinte paciente recebeu alta:\n");
				printf("%06d | %s\n", paciente_get_id(p), paciente_get_nome(p)); 
				}

				break;

			case 7:
				puts("--- Adicionar Procedimento ---\n");

				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				puts("Procedimento novo: ");
				scanf(" %100[^\n]", proced);

				if (adicionar_procedimento(r, id, proced)) 
					printf("Adição de procedimento bem-sucedida.\n");
				
				else {
					printf("Houve um erro na adição de procedimento.\n");
					printf("Por favor, verifique se o paciente está registrado.\n");
				}
				
				break;



			
			case 8:
				puts("--- Desfazer Procedimento ---\n");

				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				if (desfazer_procedimento(r, id))
					printf("Remoção de procedimento bem-sucedida.\n");
				
				else {
					printf("Houve um errona adição de procedimento.\n");
					printf("Por favor, verifique se o paciente está registrado ou se o histórico dele está vazio.\n");
				}
				break;


			case 9:
				puts("--- Mostrar Histórico de Paciente ---\n");
				
				puts("ID do paciente: ");
				
				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				if(!mostrar_historico(r, id)) puts("Por favor, verifique se o paciente está registrado");

				break;
			
			case 10:
				sair(&r, &f);
				puts("Registros e Fila salvos!\n");
				break;




			default:
				puts("Operação inválida!\n");
		}

		if (op == 10) break;

		printf("\n\nPressione enter para continuar...");
		getchar(); //pega o enter do scanf
		getchar(); //Pegar o enter do "Pressione enter para continuar..."
	}
	
	return 0;
}

