#include<stdio.h>
#include<string.h>

float media(char *comando){
	int i, n, soma = 0, somap = 0;
	float media;
	
	if(*comando == 'A' || strcmp(comando, "ARITMETICA") == 0 || strcmp(comando, "aritmetica") == 0){
		printf("Digite a quantidade de inputs: \n");		
		scanf("%d", &n);
		int ari[n];
		printf("Digite uma input por linha: \n");
		
		for(i=0;i<n;i++){
			scanf("%d", &ari[i]);
			soma += ari[i];
		}
		
		media = (float)soma/n;

		return media; 
	}
	if(*comando == 'P' || strcmp(comando, "PONDERADA") == 0 || strcmp(comando, "ponderada") == 0){
		printf("Digite a quantidade de inputs: \n");		
		scanf("%d", &n);
		int pon[n], peso[n];
		printf("Digite uma input e seu peso por linha: \n");

		for(i=0;i<n;i++){
			scanf("%d %d", &pon[i], &peso[i]);
			soma += pon[i]*peso[i];
			somap += peso[i];
		}
		
		media = (float)soma/somap;
	
		return media;
	}
	else{
		printf("Comando Inválido\n");
	}
}

int main(){
	
	float mediaf;
	char comando[10];
	scanf("%s", comando);

	mediaf = media(comando);
	
	printf("%.2f\n", mediaf);

	return 0;
}
