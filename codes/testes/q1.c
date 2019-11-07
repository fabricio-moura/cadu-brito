#include<stdio.h>

typedef struct data{
	int d, h, m, s, ts;
} data; 

int main(){
	
	FILE *inputq1;
	FILE *duracao;
	inputq1 = fopen("inputq1.txt", "r");
	duracao = fopen("duracao.txt", "w");

	int dif_ts;
	data dia1, dia2, res;

	fscanf(inputq1, "Dia %d", &dia1.d);
	fscanf(inputq1, "%d : %d : %d\n", &dia1.h, &dia1.m, &dia1.s);
	fscanf(inputq1, "Dia %d", &dia2.d);
	fscanf(inputq1, "%d : %d : %d", &dia2.h, &dia2.m, &dia2.s);

	dia1.ts = dia1.d*86400 + dia1.h*3600 + dia1.m*60 + dia1.s;
	dia2.ts = dia2.d*86400 + dia2.h*3600 + dia2.m*60 + dia2.s;
	dif_ts = dia2.ts - dia1.ts;

	res.d = dif_ts/86400;
	res.h = (dif_ts - res.d*86400)/3600;
	res.m = (dif_ts - res.d*86400 - res.h*3600)/60;
	res.s = dif_ts - res.d*86400 - res.h*3600 - res.m*60;

	fprintf(duracao, "%d dia(s)\n", res.d);
	fprintf(duracao, "%d hora(s)\n", res.h);
	fprintf(duracao, "%d minuto(s)\n", res.m);
	fprintf(duracao, "%d segundo(s)\n", res.s);

	fclose(inputq1);
	fclose(duracao);

	return 0;
}
