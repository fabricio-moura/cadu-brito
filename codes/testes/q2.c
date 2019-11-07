#include<stdio.h>

typedef struct pessoa{
	char nome[100];
	int idade, salario;
} pessoa;

void registrar_pessoa (pessoa *input){
	printf("Digite o nome:\n");
	fgets(input->nome, 100, stdin);
	printf("Digite a idade:\n");
	scanf("%d", &input->idade);
	printf("Digite o salario:\n");
	scanf("%d", &input->salario);
}

void listar_pessoa (pessoa *input){
	printf("\n");
	printf("Nome: %s", input->nome);
	printf("Idade: %d\n", input->idade);
	printf("Salario: R$ %d\n", input->salario);
	printf("\n");
}

int main(){	

	pessoa input;
	int comando;
	
	while(1){
		printf("Para registrar uma pessoa, digite 1\n");
		printf("Para listar uma pessoa, digite 2\n");
		printf("Para sair, digite 3\n");
		printf("\n");

		scanf("%d", &comando);
		getchar();
		
		if(comando == 3){
			break;
		}
		else if(comando == 1){
			registrar_pessoa (&input);
		}
		else if(comando == 2){
			listar_pessoa (&input);
		}
		else{
			printf("\n");
			printf("Comando inválido\n");
			printf("\n");
		}
	}

	return 0;
}
