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

int InsereFilho(No* no, No* novo){
	
	if (strcmp(no->nome,novo->nome) == 0){
		return 0;
	}
	
	if (strcmp(no->nome,novo->nome) < 0){
		if (no->filho_esq == NULL){
			no->filho_esq = novo;
			
			return 1;
		}
		else{
			return InsereFilho(no->filho_esq,novo);
		}
	}
	
	if (strcmp(no->nome,novo->nome) > 0){
		if (no->filho_dir == NULL){
			no->filho_dir = novo;
			
			return 1;
		}
		else{
			return InsereFilho(no->filho_dir,novo);
		}
	}
	
	return 0;
}

int InsereNo(ArvoreB* arvore, No* no){
	
	if (arvore->raiz == NULL){
		arvore->raiz = no;
		
		return 1;
	}	
	
	InsereFilho(arvore->raiz,no);

	return 1;
}

int main()
{
	
	return 0;
}
