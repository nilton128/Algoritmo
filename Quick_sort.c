#include<stdio.h>
#include<stdlib.h>
void aloca(int ta){
     int *vet,i;
     vet=(int*)malloc(sizeof(int)*ta);
     printf("\tDigite\n");
     for(i=0;i<ta;i++){
		scanf("%d",&vet[i]);
        }
     printf("Vetor desordenado:\n");
     for(i = 0; i < ta; i++){
        printf("%d ", vet[i]);
     }
     Quick(vet,0,ta);
     printf("\n");
     printf("Vetor ordenado:\n");
     for(i = 0; i < ta; i++){
        printf("%d ", vet[i]);
   }

}
int Quick(int vetor[], int inicio, int fim){
   int pivo, aux, i, j, meio;
   i = inicio;
   j = fim;
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   do{
      while (vetor[i] < pivo)
          i = i + 1;
      while (vetor[j] > pivo)
          j = j - 1;
          if(i <= j){
             aux = vetor[i];
             vetor[i] = vetor[j];
             vetor[j] = aux;
             i = i + 1;
             j = j - 1;
         }
   }while(j > i);
   if(inicio < j)
     Quick(vetor, inicio, j);
   if(i < fim)
     Quick(vetor, i, fim);
}
int main(){
   int tam;
   printf("Digite a quatidade");
   scanf("%d",&tam);
   aloca(tam);
   printf("\n");
}

