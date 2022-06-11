/*
Aluno: Lemersom Fernandes Filho     RA: 2410176

UTFPR - CP
AS32F - Tecnicas de Programacao - N12A
P2 - Alocacao Dinamica de Memoria e Struct
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct equip {
	int codigoequipamento;  //nesse caso serao definidos como sendo a posicao dentro do vetor ex: 0, 1, 2, 3...
	char equipamento[30];
	float potencia;
	int tempoativo;
	float consumonomes;
}typedef equipamento;

void preenche_vetor(equipamento*, int, int*);
equipamento* aloca_vetor(int);
equipamento* realoca_vetor(equipamento *, int);
float calc_consumo(float, int);
void ordpotcresc(equipamento*, int);   // ordena potencia crescente
void ordconsdecresc(equipamento*, int);  // ordena consumo decrescente
void escreve_vetor(equipamento*, int);
int escolha(); // codigo do eq com maior ou menor consumo

int n; // tamanho ou quantidade

int main(){
	int opcao, maiorcons, menorcons, *novo_n;
	equipamento *eq;
	
	printf("Digite quantos equipamentos serao incluidos: ");
	scanf("%d", &n);
	
	eq = aloca_vetor(n);
	
	preenche_vetor(eq, n, novo_n);
	
	n = novo_n[0]; // n apos o realloc
	
	ordpotcresc(eq, n); 
	ordconsdecresc(eq, n); 

	maiorcons = eq[0].codigoequipamento;
	menorcons = eq[n - 1].codigoequipamento;

	opcao = escolha();
	if(opcao == 1){
		printf("\nCodigo do equipamento com maior consumo: %d", maiorcons);
	}
	else if(opcao == 2){
		printf("\nCodigo do equipamento com menor consumo: %d", menorcons);
	}
	
	free(eq);
	
	return 0;
}

int escolha(){
	int opcao;
	printf("\n\n\n1 - Mostrar codigo do equipamento com maior consumo");
	printf("\n2 - Mostrar codigo do equipamento com menor consumo\nOpcao escolhida: ");
	scanf("%d", &opcao);
	
	return opcao;
}

void escreve_vetor(equipamento *eq, int n){
	int i;
	
	for(i = 0; i < n; i++){
		printf("\n");
    	printf("\nCodigo: %d", eq[i].codigoequipamento);
		printf("\nEquipamento: %s", eq[i].equipamento);
		printf("\nPotencia: %.2f", eq[i].potencia);
		printf("\nTempo Ativo: %d", eq[i].tempoativo);
		printf("\nConsumo: %.2f", eq[i].consumonomes);
	}
}

void preenche_vetor(equipamento *eq, int n, int *novo_n){
	int i, perg, n1;
	
	for(i = 0; i < n; i = i + 1){
		eq[i].codigoequipamento = i;
		printf("\nDados do %d equipamento", i + 1);
		printf("\nEquipamento: ");
		fflush(stdin);
		gets(eq[i].equipamento);
		printf("Potencia(W): ");
		scanf("%f", &eq[i].potencia);
		while(eq[i].potencia < 1 || eq[i].potencia > 7500){
			printf("\nERRO! Potencia deve estar entre 1 e 7500 (W)\nTente de novo, Potencia: ");
			scanf("%f", &eq[i].potencia);
		}
		printf("Tempo ativo(min): ");
		scanf("%d", &eq[i].tempoativo);
		while(eq[i].tempoativo < 1 || eq[i].tempoativo > 600){
			printf("\nERRO! Tempo ativo deve estar entre 1 e 600 (min)\nTente de novo, Tempo ativo: ");
			scanf("%d", &eq[i].tempoativo);
		}
		eq[i].consumonomes = calc_consumo(eq[i].potencia, eq[i].tempoativo);
		
		
		if(i == n - 1){
			printf("\nDeseja cadastrar mais equipamentos? (1) - Sim (2) - Nao ");
			scanf("%d", &perg);
			if(perg == 1){
				printf("\nQuantos? ");
				scanf("%d", &n1);    // n1 = quantos a mais serao realocados
				eq = realoca_vetor(eq, n1);
				n = n + n1;
			}
		}
	}
	novo_n[0] = n;
}

float calc_consumo(float pot, int temp){
	float consumo;
	
	consumo = (pot * (temp/60) * 30) / 1000;  //div por 60 para transformar em horas
										//multi por 30 por causa da qtd de dias do mes
	
	return consumo;
}

void ordpotcresc(equipamento *eq, int n){
	int i, j;
	equipamento aux;
	
	for(i = 0; i < n - 1; i = i + 1){
		
		for(j = i + 1; j < n; j = j + 1){
			if(eq[i].potencia > eq[j].potencia){
				aux = eq[i];
				eq[i] = eq[j];
				eq[j] = aux;
			}
		}
	}
	printf("\n\t Em ordem crescente de potencia: "); 
	escreve_vetor(eq, n);
	
}

void ordconsdecresc(equipamento *eq, int n){
	int i, j;
	equipamento aux;
	
	for(i = 0; i < n - 1; i = i + 1){
		
		for(j = i + 1; j < n; j = j + 1){
			if(eq[i].consumonomes < eq[j].consumonomes){
				aux = eq[i];
				eq[i] = eq[j];
				eq[j] = aux;
			}
		}
	}
	
	printf("\n\n\t Em ordem decrescente de consumo: "); 
	escreve_vetor(eq, n);
}

equipamento* aloca_vetor(int n){
	
	equipamento *eq;
	
	if(malloc(n * sizeof(equipamento)) == NULL){
		printf("\nNao ha memoria suficiente para alocar o vetor");
		exit(0);
	}
	
	eq = malloc(n * sizeof(equipamento));
	
	return eq;
}

equipamento* realoca_vetor(equipamento *eq, int n1){
	
	if(realloc(eq, n * sizeof(equipamento)) == NULL){
		printf("\nNao ha memoria suficiente para realocar o vetor");
	}
	
	eq = realloc(eq, (n + n1) * sizeof(equipamento));
	
	return eq;
}
