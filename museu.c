#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef int TIPOCHAVE;
typedef int bool;

typedef struct{
	char nome[100];
	float entrada;
	char cidade[100];
	char pais[100];
	int nota;
} MUSEU;

typedef struct auxElem{
	MUSEU museu;
	struct auxElem* ant;
	struct auxElem* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct{
	PONT cabeca;
} DEQUE;

void inicializarDeque(DEQUE* d){
	d->cabeca = (PONT) malloc(sizeof(ELEMENTO));
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant = d->cabeca;
}

// ################ QUESTÃO a)
bool inserirMuseuInicio(DEQUE* d, MUSEU museu){
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->museu = museu;
	novo->ant = d->cabeca;
	novo->prox = d->cabeca->prox;
	d->cabeca->prox = novo;
	novo->prox->ant = novo;
	return true;
}

// ################ QUESTÃO b)
bool inserirMuseuFim(DEQUE* d, MUSEU museu){
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->museu = museu;
	novo->prox = d->cabeca;
	novo->ant = d->cabeca->ant;
	d->cabeca->ant = novo;
	novo->ant->prox = novo;
	return true;
}

// ################ QUESTÃO c)
void exibirMuseus(DEQUE* d){
	PONT end = d->cabeca->prox;
	printf("Lista completa: ");
	while (end != d->cabeca){
		printf("\n\tNome: %s", end->museu.nome);
		printf("\n\tPais: %s", end->museu.pais);
		printf("\n\tCidade: %s", end->museu.cidade);
		printf("\n\tNota: %i", end->museu.nota);
		printf("\n\tValor da entrada: R$%.2f\n", end->museu.entrada);	
		end = end->prox;
	}
	printf("\nFIM\n");
}


// ################ QUESTÃO d)
void exibirMuseusMaior3(DEQUE* d){
	PONT end = d->cabeca->prox;
	printf("Lista de museus com nota maior do que 3: ");
	while (end != d->cabeca){
		if(end->museu.nota > 3){
			printf("\n\tNome: %s", end->museu.nome);
			printf("\n\tPais: %s", end->museu.pais);
			printf("\n\tCidade: %s", end->museu.cidade);
			printf("\n\tNota: %i", end->museu.nota);
			printf("\n\tValor da entrada: R$%.2f\n", end->museu.entrada);	
		}
		end = end->prox;
	}
	printf("\nFIM\n");
}


// ################ QUESTÃO e)
void exibirMuseusBrasil(DEQUE* d){
	PONT end = d->cabeca->prox;
	printf("Lista dos museus no Brasil: ");
	while (end != d->cabeca){
		if(!strcmp(end->museu.pais, "BRASIL")){
			printf("\n\tNome: %s", end->museu.nome);
			printf("\n\tPais: %s", end->museu.pais);
			printf("\n\tCidade: %s", end->museu.cidade);
			printf("\n\tNota: %i", end->museu.nota);
			printf("\n\tValor da entrada: R$%.2f\n", end->museu.entrada);	
		} 
		end = end->prox;
	}
	printf("\nFIM\n");
}

MUSEU inserirNovoMuseu(){
	MUSEU novoMuseu;
	char brasil[100] = "Brasil";
	printf("\tDigite o nome do museu: ");
	gets(novoMuseu.nome);
	printf("\n\tDigite o pais do museu: ");
	gets(novoMuseu.pais);
	int i;
	for(i = 0; i < strlen(novoMuseu.pais);i++){
		novoMuseu.pais[i] = toupper(novoMuseu.pais[i]);
	}
	printf("\n\tDigite a cidade do museu: ");
	gets(novoMuseu.cidade);
	printf("\n\tDigite a nota do museu: ");
	scanf("%d", &novoMuseu.nota);
	while(novoMuseu.nota < 0 || novoMuseu.nota > 5){
		printf("\n\tNota invalida.\n\tPor favor digite uma nota de 0 a 5: ");
		scanf("%d", &novoMuseu.nota);
	}
	printf("\n\tDigite o valor da entrada do museu: R$");
	scanf("%f", &novoMuseu.entrada);
	return novoMuseu;
}

void menu(){
	system("cls");
	printf("\t##### MENU #####\n\n");
	printf("\t1 - Inserir museu no inicio da lista\n");
	printf("\t2 - Inserir museu no final da lista\n");
	printf("\t3 - Listar todos os museus\n");
	printf("\t4 - Listar todos os museus com nota superior a 3\n");
	printf("\t5 - Listar todos os museus do Brasil\n");
	printf("\t6 - Sair\n\n\n\t");
}

int main(void){	
	int escolha;	
	DEQUE* d = (DEQUE*) malloc(sizeof(DEQUE));
	inicializarDeque(d);
	
	do{
		menu();
		
		scanf("%d", &escolha);
		system("cls");
		setbuf(stdin, NULL);
		
		switch(escolha){
			case 1:				
				if(inserirMuseuInicio(d, inserirNovoMuseu())) printf("\n\n\t\tSALVO NO INICIO COM SUCESSO");
				else printf("\n\n\t\tFALHA AO SALVAR");				
			break;
			
			case 2:
				if(inserirMuseuFim(d, inserirNovoMuseu())) printf("\n\n\t\tSALVO NO FINAL COM SUCESSO");
				else printf("\n\n\t\tFALHA AO SALVAR");
			break;
			
			case 3:
				exibirMuseus(d);
			break;
			
			case 4:
				exibirMuseusMaior3(d);
			break;
			
			case 5:
				exibirMuseusBrasil(d);
			break;
			
			case 6:
				printf("\n\n\t\tSaindo");
			break;
			
			default:
				printf("\n\n\t\tOpcao invalida. Por favor digite novamente");
		}
		getch();
		
	}while(escolha != 6);
	return 0;
}
