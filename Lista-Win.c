#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
/* =================DEFINICAO DE TIPOS==================================== */
    typedef int TipoChave;
    typedef struct {
        int Chave;
        /* outros componentes */
    }TipoItem;

    typedef struct Celula_str *Apontador;

    typedef struct Celula_str {
        TipoItem Item;
        Apontador Prox;
    }Celula;

    typedef struct {
        Apontador Primeiro, Ultimo;
    }TipoLista;

/*============FUNCOES DA ESTRUTURA==============*/
    void FLVazia(TipoLista *Lista){
        Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
        Lista->Ultimo = Lista->Primeiro;
        Lista->Primeiro->Prox = NULL;
    }

    int Vazia(TipoLista Lista){
        return (Lista.Primeiro == Lista.Ultimo);
    }

    void Insere(TipoItem x, TipoLista *Lista){
        Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
        Lista->Ultimo = Lista->Ultimo->Prox;
        Lista->Ultimo->Item = x;
        Lista->Ultimo->Prox = NULL;
    }

    /*Funcao Retira modificada para remover o item da lista atrav�s da Chave do Item*/
    void Retira(int chave, TipoLista *Lista, TipoItem *Item){
        Apontador q, Aux;
        Aux = Lista->Primeiro;
        q = Aux->Prox;
        if (Vazia(*Lista) || Aux == NULL || Aux->Prox == NULL) {
            printf("\n\tLista vazia ou posicao nao existe!\n");
            return;
        }
        while (q != NULL){
            if (q->Item.Chave == chave){
                *Item = q->Item;
                Aux->Prox = q->Prox;
                if (Aux->Prox == NULL)
                    Lista->Ultimo = Aux;
                free(q);
                return;
            }
            q = q->Prox;
            Aux = Aux->Prox;
        }
    }

    void Imprime(TipoLista Lista){
        Apontador Aux;
        Aux = Lista.Primeiro->Prox;
        if (Vazia(Lista)){
            printf("\n\tLista vazia!\n");
            return;
        }
        while (Aux != NULL){
            /*printf("Nome: %s\n",Aux->Item.nome);*/
            printf("\n\t%d\n", Aux->Item.Chave);
            Aux = Aux->Prox;
        }
    }

    /*funcao de ordenacao para lista encadeada*/
    void Selecao(TipoLista *Lista){
        TipoItem Item;
        Apontador Aux, Tmp;
        int i,j;
        Aux = Lista->Primeiro->Prox;
        while(Aux->Prox!=NULL){
            Tmp = Aux->Prox;
            while(Tmp!=NULL){
                if(Tmp->Item.Chave<Aux->Item.Chave){
                    Item = Aux->Item;
                    Aux->Item=Tmp->Item;
                    Tmp->Item=Item;
                }
                Tmp = Tmp->Prox;
            }
            Aux = Aux->Prox;
        }
    }

    void Salvar(TipoLista Lista,FILE *pFile){
            Apontador Aux;
            Aux = Lista.Primeiro->Prox;
            if (Vazia(Lista)){
                printf("Erro:Lista vazia!\n");
                system("pause");
                return;
            }
            while (Aux != NULL){
                fprintf (pFile, "%d\n",Aux->Item.Chave);
                Aux = Aux->Prox;
            }
            printf("\tSalvo\n");
            system("pause");
        }

    int imprima(TipoLista Lista,int k){
            Apontador Aux;
            Aux = Lista.Primeiro->Prox;
            if (Vazia(Lista)){
                printf("Erro:Lista vazia!\n");
                system("pause");
                return;
            }
            while (Aux != NULL){
                if(Aux->Item.Chave==k){
                    return(1);
                }
                Aux = Aux->Prox;
            }
            printf("\n\tNumero nao encontrado\n");
            system("pause");
            return(0);
        }

/* =============================FUNCAO PRINCIPAL============================================= */
int main(){
    FILE *ArqDados;
	TipoLista lista;
	TipoItem item;
	Apontador p;
	int i, j, k, n,op;
	float  tamanho=0;
	char resp;
	FLVazia(&lista);
    do{
		do{
			printf("\n-----------------LISTA---------------------\n\n");
			printf("\n\t1-Inserindo\n");
			printf("\t2-Exiba a Lista\n");
			printf("\t3-Ordenado\n");
			printf("\t4-Retirando\n");
			printf("\t5-Salvar\n");
			printf("\t6-Sair\n");
			printf("\t\tOPCAO.:");
			scanf("%d",&op);
			system("cls");
    }while(op<0||op>6);
	if(op==1){/*Inserindo*/
       item.Chave=i;
       do{
            printf("\n\n\tDigite o valores.:");
            fflush(stdin);
            scanf("%d",&item.Chave);
            Insere(item, &lista);
            printf("\n\tDeseja digita novamente? (S/N).:");
            fflush(stdin);
            scanf("%c",&resp);
            system("cls");
        }while(resp=='s');
	}
    else if(op==2){/* Mostrando a lista*/
        printf("\t\t------Mostra Lista--------\n");
        Imprime(lista);
        system("pause");
        system("cls");
	}
    else if(op==3){/*Ordenação da Lista*/
        printf("----------Ordenado------------\n");
        if(Vazia(lista)){
            Imprime(lista);
        }
        else{
            Selecao(&lista);
            Imprime(lista);
        }
        system("pause");
        system("cls");
	}
    else if(op==4){/*Removendo*/
        printf("----------Removendo------------\n");
        /*Imprime(lista);*/
        if(Vazia(lista)){
             Imprime(lista);
        }
        else{
            Imprime(lista);
            do{
                printf("\n\tQual deseja remover.:");
                scanf("%d",&k);
                if(imprima(lista,k)){
                    Retira(k, &lista, &item);
                    printf("\n\tRetirou: %d\n", item.Chave);
                }
                fflush(stdin);
                printf("\n\tDeseja Remover novamente? (S/N).:");
                fflush(stdin);
                scanf("%c",&resp);
            }while(resp=='s');
        }
    system("pause");
    system("cls");
	}
	else if(op==5){/*Salvando em arquivo*/
			ArqDados = fopen ("Vestibular.txt","w");// cria o arquivo
			Salvar(lista,ArqDados);// salva os dados no documento
			fclose (ArqDados);// fecha a arquivo
			system("cls");
    }
    else if(op==6){/*Fechando o programa*/
			exit(1);
    }
	}while(op!=6);
	/*return(0);*/
}
