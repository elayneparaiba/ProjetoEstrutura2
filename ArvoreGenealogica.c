#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{char* nome;
				struct Pessoa* pessoa;
				struct No* filho_dir;
				struct No* filho_esq;
				} No;
				
typedef struct ArvoreB{No* raiz;
				} ArvoreB;
				
typedef struct Pessoa{char* nome;
				char sexo;
				struct Pessoa* pai;
				struct Pessoa* irmao;
				struct Pessoa* conjuge;
				struct Pessoa* filho1;
				} Pessoa;
				
ArvoreB* CriaArvore (){
	ArvoreB* arvore;
	
	arvore = (ArvoreB*) malloc(sizeof(ArvoreB));
	
	return arvore;
}
				
int InicializaArvore (ArvoreB* arvore){
	arvore->raiz = NULL;
	return 1;
}

No* CriaNo (){
	No* novo;
	
	novo = (No*) malloc(sizeof(No));
	
	return novo;
}
				
int InicializaNo (No* no, Pessoa* pessoa){
	
	no->nome = pessoa->nome;
	no->pessoa = pessoa;
	no->filho_dir = NULL;
	no->filho_esq = NULL;
	
	return 1;
}

Pessoa* CriaPessoa (){
	Pessoa* novo;
	
	novo = (Pessoa*) malloc(sizeof(Pessoa));
	
	return novo;
}
				
int InicializaPessoa (Pessoa* pessoa,char* nome, char sexo, Pessoa* pai){
	
	pessoa->nome = nome;
	pessoa->sexo = sexo;
	pessoa->pai = pai;
	pessoa->irmao = NULL;
	pessoa->conjuge = NULL;
	pessoa->filho1 = NULL;
	
	return 1;
}

int InsereNoFilho(No* no, No* novo){
	
	if (strcmp(no->nome,novo->nome) == 0){
		return 0;
	}
	
	if (strcmp(no->nome,novo->nome) < 0){
		if (no->filho_esq == NULL){
			no->filho_esq = novo;
			
			return 1;
		}
		else{
			return InsereNoFilho(no->filho_esq,novo);
		}
	}
	
	if (strcmp(no->nome,novo->nome) > 0){
		if (no->filho_dir == NULL){
			no->filho_dir = novo;
			
			return 1;
		}
		else{
			return InsereNoFilho(no->filho_dir,novo);
		}
	}
	
	return 0;
}

int InsereNo(ArvoreB* arvore, No* no){
	
	if (arvore->raiz == NULL){
		arvore->raiz = no;
		
		return 1;
	}	
	
	return InsereNoFilho(arvore->raiz,no);
}

int VerificaNoPessoa(No* percorre,char* nome){
	
	if (strcmp(percorre->nome,nome)){
		return 1;
	}
	
	if (strcmp(percorre->nome,nome) < 0){
		return VerificaNoPessoa(percorre->filho_esq,nome);
	}
	
	if (strcmp(percorre->nome,nome) > 0){
		return VerificaNoPessoa(percorre->filho_dir,nome);
	}
	
	return 0;
}

int VerificaPessoa (ArvoreB* arvore,char* nome){
	
	if (arvore->raiz == NULL){
		return 0;
	}	
	
	return VerificaNoPessoa(arvore->raiz,nome);
}

int NascePessoa(ArvoreB* arvore,int opcao){
	No *novo;
	Pessoa *nova_pessoa;
	Pessoa *pai = NULL;
	char* nome_pai = (char*) malloc(sizeof(char));
	
	char *nome = (char*) malloc(sizeof(char));
	char sexo;
				
	novo = CriaNo();
	nova_pessoa = CriaPessoa();
	
	printf("Informe o nome:\n");
	scanf("%s",nome);
	printf("Informe o sexo (F / M):\n");
	scanf("%c",&sexo);
	
	if (opcao == 1){			//sem pai
		InicializaPessoa(nova_pessoa,nome,sexo,pai);
		InicializaNo(novo,nova_pessoa);
	}
	else{      //com pai
		printf("Informe o nome pai\n");
		scanf("%s",nome_pai);
		if (VerificaPessoa(arvore,nome_pai) == 0){
			printf("O pai informado não está na arvore");
			return 0;
		}
		else{
			
		}
	}
	return 1;
}

int main()
{
	int opcao = -1;
	ArvoreB *arvore;
	
	arvore = CriaArvore();
	
	InicializaArvore(arvore);

		
	while(opcao != 0) {
		//system("clear"); //se for rodar no linux
		//system("cls"); // se for rodar no windows
		printf("=======================ARVORE GENEALÓGICA=======================\n\n");
		printf("1. Insere sem pai\n");
		printf("2. Insere com pai\n");
		printf("3. Informa casamento\n");
		
		scanf("%d",&opcao);

		switch(opcao) {

			case 1: 
			case 2: {
				NascePessoa(arvore,opcao);
				break;
			}			
			case 3:{
				break;
			}
		}
	}
	
	getchar();
	
	return 0;
}
