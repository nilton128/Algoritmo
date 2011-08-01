#include<stdio.h>
#include<stdlib.h>
void selecao(int ta){
     int *vet,temp,i,j,min,k;
     vet=(int*)malloc(sizeof(int)*ta);
     printf("\tDigite\n");
     for(i=0;i<ta;i++){
		scanf("%d",&vet[i]);
        }
     for(i=0;i<ta-1;i++){
		min = i;
        for(j=i+1;j<ta;j++){
            if (vet[j]<vet[min]){
                min = j;
                }
        }
        temp=vet[i];
        vet[i]=vet[min];
        vet[min]=temp;
    }
    for (k = 0;k<ta;k++){
    printf("\n%d ", vet[k]);
    }
}
int main(){
    int num;
    printf("Digite a quantidade de numeros : " );
    scanf("%d",&num);
    selecao(num);
    getchar();
    return(0);
}
