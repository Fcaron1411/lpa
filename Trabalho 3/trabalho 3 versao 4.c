#include <stdlib.h>
#include <stdio.h>

struct CELULA {  //estrutura de cada componente da matriz
  int linha;
  int coluna;
  float valor;
  struct CELULA *direita;
  struct CELULA *abaixo;
};

typedef struct CELULA CELULA;

struct m_e {  //estrutura da matriz, inicio da matriz
  CELULA **linhas;
  CELULA **colunas;
  int num_linhas;
  int num_colunas;
};

typedef struct m_e MATRIZ_ESPARSA;

MATRIZ_ESPARSA *criar_matriz(int num_linhas, int num_colunas) {  //função que cria os primeiros ponteiros para que assim
  MATRIZ_ESPARSA *mat = (MATRIZ_ESPARSA*) malloc(sizeof(MATRIZ_ESPARSA));  //os elementos sejam inseridos
  if (mat != NULL) {
    int i;
    mat->num_colunas = num_colunas; //passa para estrutura da matriz o numero
    mat->num_linhas = num_linhas;   //de linhas e colunas
    mat->colunas = (CELULA**) malloc(sizeof(CELULA*)*num_colunas);
    mat->linhas = (CELULA**) malloc(sizeof(CELULA*)*num_linhas);

    if (mat->colunas != NULL && mat->linhas != NULL) {
      for (i = 0; i < num_colunas; i++) {
        mat->colunas[i] = (CELULA *) malloc(sizeof (CELULA));  //aloca memoria para todas os ponteiros de colunas
        mat->colunas[i]->abaixo = NULL;  //faz a celula apontar para a celula de baixo da mesma coluna
      }

      for (i = 0; i < num_linhas; i++) {
        mat->linhas[i] = (CELULA *) malloc(sizeof (CELULA)); //aloca memoria para os ponteiros de linhas
        mat->linhas[i]->direita = NULL; //faz todos os ponteiros de cada linha apontar para NULL
      }
    }
  }
  return mat; //retorna a matriz alocada
}

void insercao(MATRIZ_ESPARSA *matriz, int lin, int col, float val) {  //função que insere uma celula na matriz
  if (lin < matriz->num_linhas && col < matriz->num_colunas) {  //verifica se os valores passados para a função são validos
    CELULA *aux = matriz->linhas[lin];

    while (aux->direita != NULL && aux->direita->coluna <= col) {//procura a coluna certa para inserir a celula
      aux = aux->direita;
    }

    if (aux->coluna == col) {  //se ja existir uma celula aonde deseja inserir essa nova celula
      aux->valor = val;        //o programa apenas muda o valor
    } else {                   //caso não exista uma celula no local desejado o programa ira
      CELULA *pnovo = (CELULA *) malloc(sizeof (CELULA));  //alocar a memoria para a nova celula
      if (pnovo != NULL) {
        pnovo->linha = lin;  //ira inserir os valores desejados na nova celula
        pnovo->coluna = col;
        pnovo->valor = val;
        pnovo->direita = aux->direita;  //ira fazer os ponteiros da nova celula apontar para os devidos lugares...
        aux->direita = pnovo;

        aux = matriz->colunas[col];
        while (aux->abaixo != NULL && aux->abaixo->linha <= lin) {
          aux = aux->abaixo;
        }

        pnovo->abaixo = aux->abaixo;
        aux->abaixo = pnovo;
      }
    }
    return;
  }
  return;
}

float localizador(MATRIZ_ESPARSA *matriz, int lin, int col) {  //função que localiza uma posição na matriz e acha o valor
  if (lin < matriz->num_linhas && col < matriz->num_colunas) { //dessa posição
    CELULA *aux = matriz->linhas[lin];  //faz o aux percorrer na linha desejada
    while (aux->direita != NULL && aux->direita->coluna <= col) { //acha a coluna desejada
      aux = aux->direita;
    }

    if (aux->coluna == col) {  //se existir algo ja inserido na matriz na posição desejada
      return aux->valor;       //a função retorna o valor encontrado
    }
  }
  return 0;  //caso o usuario ainda não tenha inserido nada na posição procurada
}            //o programa entende que existe o numero 0 nessa posição

void apagar_matriz(MATRIZ_ESPARSA **matriz) {  //função que apaga a matriz
  int i;
  for (i = 0; i < (*matriz)->num_linhas; i++) {  //passa de linha em linha
    CELULA *aux = (*matriz)->linhas[i]->direita;

    while (aux != NULL) {  //da free em uma linha até chegar a NULL
      CELULA *temp = aux;
      aux = aux->direita;
      free(temp);
    }

    free((*matriz)->linhas[i]);
  }

  free((*matriz)->linhas);
  free((*matriz)->colunas);
  free((*matriz));
  *matriz = NULL;
}

float somalinha(MATRIZ_ESPARSA *matriz,int linha) {  //função que faz a soma de linha em linha da matriz
  int i;
  float soma=0;
  for (i = 0; i <= matriz->num_linhas; i++) {  //percorre a linha
    soma=soma+localizador(matriz, linha, i);
  }
  return soma;
}

float somacoluna(MATRIZ_ESPARSA *matriz,int coluna) {  //função analoga a de somar linhas
  int i;
  float soma=0;
  for (i = 0; i <= matriz->num_colunas; i++) {
    soma=soma+localizador(matriz, i, coluna);
  }
  return soma;
}


void main(){

    int m, n, x=1;
    int a=1;
    MATRIZ_ESPARSA *mat = NULL;
    while(a!=0){  //faz com que enquanto o usuario nao queira sair do programa o programa nao feche

        system("CLS");
        printf("\n                          MENU\n");
        printf("Digite:\n");
        printf("0 - Sair\n1 - Criar a matriz esparsa\n2 - Excluir a matriz\n3 - Consulta dos valores de uma posicao (i, j) da matriz\n");
        printf("4 - Consulta da soma dos valores de cada linha da matriz\n5 - Consulta da soma dos valores de cada coluna da matriz\n");
        printf("6 - Atribuicao de um valor na posicao (i, j) da matriz\n");
        scanf("%d", &a);

        switch (a){  //ira realizar cada caso de acordo com a escolha do usuario
            case 0:  //caso para o fim do programa
                printf("FIM\n");
                break;
            case 1:  //caso para a criação da matriz e inserção dos primeiros valores(caso desejar)
                if(mat==NULL){
                    printf("Entre com o valor de linhas e colunas da matriz a ser criada:\n");
                    scanf("%d %d",&m,&n);
                    mat = criar_matriz(m, n);  //cria uma matriz com m linhas e n colunas
                     while(x!=0){  //faz o programa ficar rodando nessa parte até que o usuario deseje sair
                        system("CLS");
                        printf("\nDigite:\n 1 - para inserir um numero na matriz \n 0 - para parar de inserir na matriz:\n\n ");
                        scanf("%d", &x);

                        while(x!=1&&x!=0){  //while de proteção caso o usuario entre com um valor incoerente
                        	printf("\nEntre com um valor valido!\n");
                        	printf("\nDigite:\n 1 - para inserir um numero na matriz \n 0 - para parar de inserir na matriz:\n\n ");
                            scanf("%d", &x);
                        	system("PAUSE");
                        	system("CLS");
						}

                        if(x!=0){
                            printf("\nDigite a linha, a coluna e o valor que deseja inserir na matriz:\n");
                            printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", m, n);

                            int linha, col;
                            float valor;
                            scanf("%d", &linha);
                            scanf("%d", &col);
                            scanf("%f", &valor);
                            while(linha>m||col>n||linha<=0||col<=0){//while de proteção caso o usuario entre com um valor incoerente
                                printf("Posicao invalida! Entre com um valor valido para a posicao \ne com o valor novamente\n");
                                printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", m, n);
                                    scanf("%d", &linha);
                                    scanf("%d", &col);
                                    scanf("%f", &valor);
                            }
                            insercao(mat, linha-1, col-1, valor);  //insere um valor na matriz
                        }
                     }
                     system("PAUSE");
                }else{  //caso a matriz nao tenha sido criada, e por isso seria impossivel inserir um valor nela,
                    printf("A matriz ja foi criada\n");  //o programa alerta o usuario sobre isso
                    system("PAUSE");
                }
                x=1;  //faz a variavel valer 1 novamente só para o caso do usuario voltar ao inicio desse caso e nao entrar
			    break; //em um while
            case 2:  //caso para se apagar a matriz interia
                if(mat!=NULL){  //
                    printf("A matriz foi apagada\n");
                    apagar_matriz(&mat);
                    system("PAUSE");
                }else{  //alerta o usuario que ainda não foi criada nenhuma matriz, logo nao tem como apagar nada
                    printf("\nA matriz ainda nao foi criada\n");
                    system("PAUSE");
                }
                break;
            case 3:  //caso que pesquisa o valor de terminada posição
                if(mat!=NULL){
                    printf("\nDigite a posicao que deseja pesquisar, sendo a primeira \nposicao a linha e a sugunda a coluna:\n");
                    printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", m, n);
                    int a, b;
                    scanf("%d %d", &a,&b);
                    while(a>m||b>n||a<=0||b<=0) { //while de proteção caso o usuario entre com um valor incoerente
                        printf("Posicao invalida! Entre com um valor valido para a posicao \ne com o valor novamente\n");
                        printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", m, n);
                            scanf("%d", &a);
                            scanf("%d", &b);
                    }
                    printf("O valor da posicao (%d,%d) eh: %.4f\n", a, b,localizador(mat,a-1,b-1));
                    system("PAUSE");
                }else{  //alerta o usuario que ainda não foi criada nenhuma matriz, logo nao ha como pesquisar um elemento
                    printf("\nA matriz ainda nao foi criada\n");
                    system("PAUSE");
                }
                break;
            case 4:  //caso que apresenta a soma de todos os elementos de uma linha da matriz
                if(mat!=NULL){
                    printf("Somas:\n");
                    int i;
                    for(i=0;i<mat->num_linhas;i++){  //passa por todas as linhas da matriz
                        printf("Soma da linha %d: ",i+1);
                        printf("%.4f\n",somalinha(mat,i));
                    }
                    system("PAUSE");
                }else{ //alerta o usuario que ainda não foi criada nenhuma matriz
                    printf("\nA matriz ainda nao foi criada\n");
                    system("PAUSE");
                }
                break;
            case 5:  //caso que apresenta a soma de todos os elementos de uma coluna da matriz. é analogo ao da soma das linhas
                if(mat!=NULL){
                    printf("Somas:\n");
                    int i;
                    for(i=0;i<mat->num_colunas;i++){
                        printf("Soma da coluna %d: ",i+1);
                        printf("%.4f\n",somacoluna(mat,i));
                    }
                    system("PAUSE");
                }else{
                    printf("\nA matriz ainda nao foi criada\n");
                    system("PAUSE");
                }
                break;
            case 6:  //caso em que o usuario insere um novo valor na matriz
                if(mat!=NULL){
                    printf("\nDigite a linha, a coluna e o valor que deseja inserir na matriz:\n");
                    printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", m, n);

                    int linha, col;
                    float valor;
                    scanf("%d", &linha);
                    scanf("%d", &col);
                    scanf("%f", &valor);
                    while(linha>m||col>n||linha<=0||col<=0) {  //while de proteção caso o usuario entre com um valor incoerente
                        printf("Posicao invalida! Entre com um valor valido para a posicao e com o valor novamente\n");
                        printf("Lembre-se que sua matriz tem %d linhas e %d colunas.\n", n, m);
                            scanf("%d", &linha);
                            scanf("%d", &col);
                            scanf("%f", &valor);
                            }
                    insercao(mat, linha-1, col-1, valor);  //insere o novo valor na matriz
                    printf("Valor adicionado\n");
                    system("PAUSE");
                }else{  //alerta o usuario que ainda não foi criada nenhuma matriz
                    printf("\nA matriz ainda nao foi criada\n");
                    system("PAUSE");
                }
                break;
            default:  //alerta o usuario que ele entrou com um valor invalido e volta para o menu principal
                printf("Valor invalido");
        }
    }
    if(mat!=NULL){  //libera a memoria caso o usuario não tenha apagado a matriz criada
        apagar_matriz(&mat);
    }
}
