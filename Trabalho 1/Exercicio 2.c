#include<stdio.h>
#include <stdlib.h>

void insertionsort(int numeros[], int tam) {
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

int main(){

    printf("        \n     ELEMENTO UNICO\n\n");

    int n;

    printf("Digite o numero de inteiros a serem analisados: ");//descobre o tamanho do vetor a ser alocado
        fflush(stdin);
        scanf("%d", &n);
        while(n<=1){ // while de segurança pois nao existe vetor com tamanho negativo nem 0
        printf("Valor invalido. Por favor insira um numero positivo maior que 1.\n");
		scanf("%d",&n);
	}

    int *v;
    v = (int*) malloc (n*sizeof(int));//aloca um vetor do tamanho ja antes especificado
    int i, j;

    printf("\n\nDigite os %d valores a serem analisados:\n", n);
        for(i=0;i<n;i++){
        scanf("%d", &v[i]);
        }

    insertionsort(v,n); //chama a funзгo para ordenar o vetor

    system("cls");

    int *vet;
    vet = (int*) malloc (n*sizeof(int));//cria novo vetor para armezenar os numeros que so aparecem uma vez
    int k=0;

    for(i=0;i<n;i++){
    if(i!=0 && i!=n-1){//analisa os inteiros do meio do vetor, ou seja, exclui-se as pontas
        if(v[i]!=v[i-1] && v[i]!=v[i+1]){//verifica se os elementos ao lado do elemento analisado sao diferentes dele
            vet[k]=v[i];//novo vetor recebe o valor que é unico no vetor inicial
            k++;
        }

    } else { if (i==0){//analisa o primeiro elemento do vetor
                if(v[i]!=v[i+1]){//verifica se o primeiro elemento й diferente do segundo
                vet[k]=v[i];
                k++;
            }
            } else {
            if(v[i]!=v[i-1]){//analisa se o ultimo valor do vetor й diferente do anterior
                vet[k]=v[i];
                }

               }

            }
    }
    if(k==0){
            printf("Nao existe elemento unico");
            } else {
            printf("os valores que so aparecem uma vez sao: ");
    for(i=0;i<k;i++){
        printf("%d ",vet[i]);//printa o vetor composto apenas de valores que sу aparecem uma vez no vetor inicial
                    }
    }

    free(v);  //liberar a memoria
    free(vet);

 return 0;
}
