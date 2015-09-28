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

    int n;

    printf("Digite o numero de inteiros a serem analisados: ");//descobre o tamanho do vetor a ser alocado
        fflush(stdin);
        scanf("%d", &n);

    int *v;
    v = (int*) malloc (n*sizeof(int));//aloca um vetor do tamanho ja antes especificado
    int i;

    printf("\n\nDigite os %d valores a serem analisados:\n", n);
        for(i=0;i<n;i++){
        scanf("%d", &v[i]);
        }

    insertionsort(v,n); //chama a fun��o para ordenar o vetor


    int menor, m, diferenca;
    menor = v[1]-v[0];//assume que a menor diferen�a sera entre os primeiros termos do vetor
    m = 0;

    for(i=1;i<n-1;i++){
        diferenca = v[i+1] - v[i];
        if(diferenca<menor){
                menor = diferenca;
                m = i;
        }
    }

    printf("\n\nA menor diferenca e: (%d) - (%d) = %d", v[m+1], v[m], menor);

return 0;

}
