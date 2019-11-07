#include<stdio.h>

void maior_pos(int *vet, int *maior, int *posicao){
	for(int i=1;i<10;i++){
		if(vet[i] > *maior){
			*maior = vet[i];
			*posicao = i;
		}
	}
}

int main(){

	int i, vet[10], maior, posicao;

	for(i=0;i<10;i++){
		scanf("%d", &vet[i]);
	}
	
	maior = vet[0];
	posicao = 0;
	
	maior_pos(vet, &maior, &posicao);

	printf("%d %d\n", maior, posicao+1);
	
	return 0;
}
