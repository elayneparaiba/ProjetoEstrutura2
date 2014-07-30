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
		printf("Não é possível inserir a mesma pessoa na arvore\n");
		return 0; 
		//não é possivel inserir um nó igual
	}
	
	if (strcmp(no->nome,novo->nome) < 0){ //se o nome procurado por menor vai para a esquerda
		if (no->filho_esq == NULL){
			no->filho_esq = novo;
			
			printf("Nó inserido na arvore\n");
			return 1;
		}
		else{
			return InsereNoFilho(no->filho_esq,novo);
		}
	}
	
	if (strcmp(no->nome,novo->nome) > 0){ //se o nome procurado por maior vai para a direita
		if (no->filho_dir == NULL){
			no->filho_dir = novo;
			
			printf("Nó inserido na arvore\n");
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
		
		printf("O nó foi inserido na raiz da arvore\n");
		return 1;
	}	
	
	return InsereNoFilho(arvore->raiz,no);
}

Pessoa* BuscaNoPessoa(No* percorre,char* nome){ //percorre os nos da arvore para verificar se a pessoa está na arvore
	
	if (strcmp(percorre->nome,nome) == 0){
		printf("Encontrou a pessoa\n");
		return percorre->pessoa;
	}
	
	if ((percorre->filho_esq != NULL) && (strcmp(percorre->nome,nome) < 0)){
		return BuscaNoPessoa(percorre->filho_esq,nome);
	}
	
	if ((percorre->filho_dir != NULL) && (strcmp(percorre->nome,nome) > 0)){
		return BuscaNoPessoa(percorre->filho_dir,nome);
	}
	
	printf("A pessoa informada não está na árvore\n");
	return NULL;
}

Pessoa* BuscaPessoa (ArvoreB* arvore,char* nome){ //Verifica se a pessoa procurada está na raiz
	
	if (arvore->raiz == NULL){
		printf("A arvore está vazia\n");
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

int NascePessoa(ArvoreB* arvore,int opcao){ //cria uma pessoa e cria um no correspondente a ela na árvore binária
	No *novo;
	Pessoa *nova_pessoa;
	Pessoa *pai = NULL;
	char *nome_pai = (char*) malloc(sizeof(char)*45);
	
	char *nome = (char*) malloc(sizeof(char)*45);
	char sexo;
	
	printf("Informe o nome:\n");
	scanf("%s",nome);
	getchar();
	printf("Informe o sexo (F / M):\n");
	scanf("%c",&sexo);
	getchar();
	
	if (opcao == 2){     //caso a pessoa a inserir tenha um pai
		printf("Informe o nome pai\n");
		scanf("%s",nome_pai);
		pai = BuscaPessoa(arvore,nome_pai);
		if (pai == NULL){
			printf("O pai informado não está na arvore\n");
			return 0;
		}
		if (VerificaCasamento(pai) == 0){
			printf("Não foi possível inserir, o pai não está casado\n");
			return 0;
		}
		if (VerificaHomem(pai) == 0){
			printf("Não foi possível inserir, o pai informado não é homem\n");
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
	
	InsereNo(arvore,novo); //a função InsereNoFilho já verifica se a pessoa já existe na arvore
	
	return 1;
}

int VerificaIrmao(Pessoa* pessoa1, Pessoa* pessoa2){ //Função para verificar se duas pessoas informadas são irmãos
	if (pessoa1->pai != NULL && pessoa2->pai != NULL && pessoa1->pai == pessoa2->pai){
		return 1;
	}
	
	return 0;
}

int CriaCasamento(ArvoreB* arvore){ //cria o casamento entre duas pessoas da arvore
	
	char* nome_conjuge1 = (char*) malloc(sizeof(char)*45);
	char* nome_conjuge2 = (char*) malloc(sizeof(char)*45);
	int sexo1,sexo2,irmaos;
	
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
		printf("Não é possível realizar casamento entre pessoas do mesmo sexo\n");
		return 0;
	}
	
	if(VerificaCasamento(conjuge1) == 1){
		printf("Não é possível realizar casamento, pois o primeiro conjuge já é casado\n");
		return 0;
	}
	
	if(VerificaCasamento(conjuge2) == 1){
		printf("Não é possível realizar casamento, pois o segundo conjuge já é casado");
		return 0;
	}
	
	if((VerificaCasamento(conjuge2) == 1) && (VerificaCasamento(conjuge2) == 1)){
		printf("Não é possível realizar casamento, pois os conjuges já são casados\n");
		return 0;
	}
	
	irmaos = VerificaIrmao(conjuge1,conjuge2);
	if (irmaos == 1){
		printf("Não é possível realizar casamento entre irmãos");
		return 0;
	}
	
	/*o impedimento de casamento entre pai e filho não é verificado, pois como para criar um filho o pai tem que estar casado,
	já cai no impedimento de pessoa já casada
	
	o impedimento de casamento entre mãe e filho não é verificado, pois como a mãe já vai estar casada já cai no 
	impedimento de pessoa já está casada*/
	
	conjuge1->conjuge = conjuge2;
	conjuge2->conjuge = conjuge1;
	printf("Casamento realizado\n");
	
	return 1;
}

Pessoa* ConsultaConjuge (ArvoreB* arvore){
	char* nome = (char*) malloc(sizeof(char)*45);
	int casada;
	
	printf("Informa o nome da pessoa que deseja consultar:\n");
	scanf("%s",nome);
	getchar();
	
	Pessoa* pessoa = BuscaPessoa(arvore,nome);
	
	if (pessoa != NULL){
		casada = VerificaCasamento(pessoa);
	
		if (casada == 1){
			printf("O conjuge da pessoa informada é:\n");
			printf("%s",pessoa->conjuge->nome);
		}
		else{
			printf("A pessoa informada não possui conjuge\n");
		}
	}
	
	return NULL;
}

/*Pessoa* ConsultaFilhos (ArvoreB* arvore){
	
	return NULL;
}*/

int ConsultaPais(ArvoreB* arvore){
	char* nome = (char*) malloc(sizeof(char)*45);
	
	printf("Informa o nome da pessoa que deseja consultar:\n");
	scanf("%s",nome);
	getchar();
	
	Pessoa* pessoa = BuscaPessoa(arvore,nome);
	
	if (pessoa != NULL){
		if (pessoa->pai != NULL){
			printf("O pai da pessoa informada é %s\n",pessoa->pai->nome);
			printf("A mãe da pessoa informada é %s\n",pessoa->pai->conjuge->nome);
		}
		else{
			printf("A pessoa não possui pais");
		}
	}
	
	return 0;
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
		
		printf("\n\n");
		printf("=======================ARVORE GENEALÓGICA=======================\n\n");
		printf("MÓDULO 1\n");
		printf("1. Insere sem pai\n");
		printf("2. Insere com pai\n");
		printf("3. Informa casamento\n");
		printf("\n");
		printf("MÓDULO 2\n");
		printf("4. Consultar conjuge\n");
		printf("5. Consultar filhos\n");
		printf("6. Consultar pais\n");
		printf("7. Consultar irmãos \n");
		printf("\n");
		printf("0. Sair\n");
		
		scanf("%d",&opcao);
		getchar();

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
			case 4:{
				ConsultaConjuge(arvore);
				break;
			}
			/*case 5:{
				ConsultaFilhos(arvore);
				break;
			}*/
			case 6:{
				ConsultaPais(arvore);
				break;
			}
		}
		
	}
	
	return 0;
}
