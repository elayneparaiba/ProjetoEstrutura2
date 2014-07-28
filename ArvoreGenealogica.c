#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{char* nome; //Estrutura dos nos da arvore binária
				struct Pessoa* pessoa;
				struct No* filho_dir;
				struct No* filho_esq;
				} No;
				
typedef struct ArvoreB{No* raiz; //Estrutura da arvore binária
				} ArvoreB;
				
typedef struct Pessoa{char* nome; //Estrutura da Pessoa com os parentescos
				char sexo;
				struct Pessoa* pai;
				struct Pessoa* irmao;
				struct Pessoa* conjuge;
				struct Pessoa* filho1;
				} Pessoa;
				
ArvoreB* CriaArvore (){ //Aloca espaço de memória para a árvore
	ArvoreB* arvore;
	
	arvore = (ArvoreB*) malloc(sizeof(ArvoreB));
	
	return arvore;
}
				
int InicializaArvore (ArvoreB* arvore){ //Inicializa a arvore colocando o nó raiz nulo
	arvore->raiz = NULL;
	return 1;
}

No* CriaNo (){ //Aloca espaço de memória para um nó
	No* novo;
	
	novo = (No*) malloc(sizeof(No));
	
	return novo;
}
				
int InicializaNo (No* no, Pessoa* pessoa){ //inicializa o nó colocando os valores
	
	no->nome = pessoa->nome;
	no->pessoa = pessoa;
	no->filho_dir = NULL;
	no->filho_esq = NULL;
	
	return 1;
}

Pessoa* CriaPessoa (){ //aloca espaço de memória para pessoa
	Pessoa* novo;
	
	novo = (Pessoa*) malloc(sizeof(Pessoa));
	
	return novo;
}
				
int InicializaPessoa (Pessoa* pessoa,char* nome, char sexo, Pessoa* pai){ //Inicializa uma pessoa colocando os valores
	
	pessoa->nome = nome;
	pessoa->sexo = sexo;
	pessoa->pai = pai;
	pessoa->irmao = NULL;
	pessoa->conjuge = NULL;
	pessoa->filho1 = NULL;
	
	return 1;
}

int InsereNoFilho(No* no, No* novo){ //Insere o nó na posição correta
	
	if (strcmp(no->nome,novo->nome) == 0){
		return 0; //não é possivel inserir um nó igual
	}
	
	if (strcmp(no->nome,novo->nome) < 0){ //se o nome procurado por menor vai para a esquerda
		if (no->filho_esq == NULL){
			no->filho_esq = novo;
			
			return 1;
		}
		else{
			return InsereNoFilho(no->filho_esq,novo);
		}
	}
	
	if (strcmp(no->nome,novo->nome) > 0){ //se o nome procurado por maior vai para a direita
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

int InsereNo(ArvoreB* arvore, No* no){ //Insere o nó na raiz para a arvore vazia
	
	if (arvore->raiz == NULL){
		arvore->raiz = no;
		
		return 1;
	}	
	
	return InsereNoFilho(arvore->raiz,no);
}

Pessoa* BuscaNoPessoa(No* percorre,char* nome){ //percorre os nos da arvore para verificar se a pessoa está na arvore
	
	if (strcmp(percorre->nome,nome)){
		return percorre->pessoa;
	}
	
	if ((percorre->filho_esq != NULL) && (strcmp(percorre->nome,nome) < 0)){
		return BuscaNoPessoa(percorre->filho_esq,nome);
	}
	
	if ((percorre->filho_dir != NULL) && (strcmp(percorre->nome,nome) > 0)){
		return BuscaNoPessoa(percorre->filho_dir,nome);
	}
	
	return NULL;
}

Pessoa* BuscaPessoa (ArvoreB* arvore,char* nome){ //Verifica se a pessoa procurada está na raiz
	
	if (arvore->raiz == NULL){
		return NULL;
	}	
	
	return BuscaNoPessoa(arvore->raiz,nome);
}

int VerificaCasamento(Pessoa* pessoa){ //verifica se a pessoa possui um conjuge
	if (pessoa->conjuge == NULL){
		return 0;
	}
		
	return 1;
}

int VerificaHomem(Pessoa* pessoa){ //verifica se a pessoa informada é homem
	if (pessoa->sexo == 'F'){
		return 0;
	}
		
	return 1;
}

int InsereIrmao(Pessoa* filho, Pessoa* irmao){ //percorre os irmaos para adicionar um novo irmão
	if (filho->irmao == NULL){
		filho->irmao = irmao;
		return 1;
	}
	else{
		return InsereIrmao(filho->irmao,irmao);
	}
}

int InserePessoaFilho (Pessoa *filho,Pessoa* pai){ //insere o primeiro filho
	if (pai->filho1 == NULL){
		pai->filho1 = filho;
		pai->conjuge->filho1 = filho;
		return 1;
	}
	else{
		return InsereIrmao(pai->filho1,filho);
	}
}

int NascePessoa(ArvoreB* arvore,int opcao){ //cria uma pessoa
	No *novo;
	Pessoa *nova_pessoa;
	Pessoa *pai = NULL;
	char* nome_pai = (char*) malloc(sizeof(char)*45);
	
	char *nome = (char*) malloc(sizeof(char)*45);
	char sexo;
	
	printf("Informe o nome:\n");
	scanf("%s",nome);
	printf("Informe o sexo (F / M):\n");
	scanf("%c",&sexo);
	
	if (opcao == 2){     //caso a pessoa a inserir tenha um pai
		printf("Informe o nome pai\n");
		scanf("%s",nome_pai);
		pai = BuscaPessoa(arvore,nome_pai);
		if (pai == NULL){
			printf("O pai informado não está na arvore");
			return 0;
		}
		if (VerificaCasamento(pai) == 0){
			printf("Não foi possível inserir, o pai não está casado");
			return 0;
		}
		if (VerificaHomem(pai) == 0){
			printf("Não foi possível inserir, o pai não é homem");
			return 0;
		}
	}
	nova_pessoa = CriaPessoa();
	InicializaPessoa(nova_pessoa,nome,sexo,pai);
	
	if (pai != NULL){ //verifica se o pai não é nulo para atualizar os vinculos da nova pessoa
		InserePessoaFilho(nova_pessoa,pai); 
	}
	
	novo = CriaNo();
	InicializaNo(novo,nova_pessoa);
	
	InsereNo(arvore,novo);
	
	return 1;
}

int CriaCasamento(ArvoreB* arvore){ //cria o casamento entre duas pessoas da arvore
	
	char* nome_conjuge1 = (char*) malloc(sizeof(char)*45);
	char* nome_conjuge2 = (char*) malloc(sizeof(char)*45);
	int sexo1,sexo2;
	
	printf("Informe o nome do primeiro conjuge:\n");
	scanf("%s",nome_conjuge1);
	printf("Informe o nome do segundo conjuge:\n");
	scanf("%s",nome_conjuge2);
	
	Pessoa* conjuge1 = BuscaPessoa(arvore,nome_conjuge1);
	Pessoa* conjuge2 = BuscaPessoa(arvore,nome_conjuge2);
	
	if ((conjuge1 == NULL) && (conjuge2 == NULL)){
		printf("Não foi possível inserir pois os conjuges não estão na arvore\n");
		return 0;
	}
	if (conjuge1 == NULL){
		printf("Não foi possível inserir pois o primeiro conjuge não existe na arvore\n");
		return 0;
	}
	if (conjuge2 == NULL){
		printf("Não foi possível inserir pois o segundo conjuge não existe na arvore\n");
		return 0;
	}
	
	sexo1 = VerificaHomem(conjuge1);
	sexo2 = VerificaHomem(conjuge2);
	
	if (sexo1 == sexo2){
		printf("Não é possível realizar casamento entre pessoas do mesmo sexo");
		return 0;
	}
	
	if((VerificaCasamento(conjuge2) == 1) && (VerificaCasamento(conjuge2) == 1)){
		printf("Não é possível realizar casamento, pois os conjuges já são casados");
		return 0;
	}
	if(VerificaCasamento(conjuge1) == 1){
		printf("Não é possível realizar casamento, pois o primeiro conjuge já é casado");
		return 0;
	}
	if(VerificaCasamento(conjuge2) == 1){
		printf("Não é possível realizar casamento, pois o segundo conjuge já é casado");
		return 0;
	}
	
	//ADICIONAR IMPEDIMENTO PARA CASAMENTOS ENTRE IRMÃOS, PAI E FILHO, E MÃE E FILHO
	
	conjuge1->conjuge = conjuge2;
	conjuge2->conjuge = conjuge1;
	
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
		printf("0. Sair\n");
		
		scanf("%d",&opcao);

		switch(opcao) {

			case 1: 
			case 2: {
				NascePessoa(arvore,opcao);
				break;
			}			
			case 3:{
				CriaCasamento(arvore);
				break;
			}
		}
	}
	
	getchar();
	
	return 0;
}