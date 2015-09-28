#include<stdio.h>
#include <stdlib.h>

void insertionsort(int numeros[], int tam) {//ordena o vetor em ordem crescente
   int i, j, eleito;
   for (i = 1; i < tam; i++){
      eleito = numeros[i];
      j = i - 1;
      while ((j>=0) && (eleito < numeros[j])) {
         numeros[j+1] = numeros[j];
         j--;
      }
      numeros[j+1] = eleito;
   }
}

void invertinsertion(int vetor[],int tm){//ordena o vetor em ordem decrescente
	int i,j,eleito;

	for (i = 1; i < tm; i++){
      eleito = vetor[i];
      j = i - 1;
      while ((j>=0) && (eleito > vetor[j])) {
         vetor[j+1] = vetor[j];
         j--;
      }
      vetor[j+1] = eleito;
   }
}


void identificador(int vetor[],int tamanho){

	int w=0;int z=0;int i=0;
	int *contador;

	contador=(int*)calloc(tamanho,sizeof(int));//o alocamento é feito com o calloc para que todas
                                               //as posiçoes do vetor se iniciem com o valor 0
	for(i=0;i<tamanho-1;i++){

		if(vetor[i]==vetor[i+1]){
			w++;
		}else{
			w=0;
		}
		contador[i]=w; //cria um vetor com as frequencias de aparições dos inteiros do vetor inicial
	}

	    invertinsertion(contador,tamanho); // ordena do maior para o menor o vetor contador;
                                           // para que o maior valor fique na posição contador[0]
        printf("O(s) valor(es) que tem maior(es) frequencia(s) e(sao):");

	for(i=0;i<tamanho;i++){

		if(vetor[i] == vetor[i+1]){
			z++;

		}else{
			z=0;
		}

		if(contador[0] == z){//aqui se compara as frequencias achadas com a maior frequencia
			printf(" %d",vetor[i]);
			z=0;
		}
	}

	for(i=0;i<tamanho;i++){
        printf("\n%d", contador[i]);
	}
}



int main(){

    int n;

    printf("Digite o numero de inteiros a serem analisados: ");//descobre o tamanho do vetor a ser alocado
        fflush(stdin);
        scanf("%d", &n);
        while(n<=0){ // while de segurança pois nao existe vetor com tamanho negativo nem 0
        printf("Valor invalido. Por favor insira um numero positivo.\n");
		scanf("%d",&n);
	}

    int *v;
    v = (int*) malloc (n*sizeof(int));//aloca um vetor do tamanho ja antes especificado
    int i ;

    printf("\n\nDigite os %d valores a serem analisados:\n", n);
        for(i=0;i<n;i++){
        fflush(stdin);
        scanf("%d", &v[i]);
        }

    insertionsort(v,n); //chama a função para ordenar o vetor

    system("cls");

    identificador(v,n); //chama a função que mostra as maiores frequencias

}
