/* UNIVERSIDADE ESTADUAL DE MONTES CLAROS - UNIMONTES
Centro de Ciências Exatas e Tecnológicas
Departamento de Ciências da Computação
Curso de Sistemas de Informação
Professor: Maurílio J. Inácio
Academicos: Nilton Rodrigues Pereira, Déborah Soares Cardoso, Henio Carlos Ferreira de Souza
Lista duplamente encadeada - alocacao dinamica*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// ESTRUTURAS DE LISTA
struct dado{
    char nome[30];
    char rua[40];
    char cidade[20];
    char estado[3];
    char cep[11];
    char tel[15];
    struct dado *prox;/*ponteiro para a próxima entrada*/
    struct dado *anterior;/*ponteiro para o registro anterior*/
}lista;

struct dado *inicio;/*ponteiro para a pimeira entrada da lista */
struct dado *passado;/*ponteiro para a última antrada */
struct dado *encontrar(char *);

//===================PROTOTIPOS de LISTA=========================
void inserir(void), pesquisa(void), salva(void);
void ler(void), listar(void);
void excluir(struct dado**,struct dado **);
void lista_en(struct dado *i, struct dado **inicio, struct dado **passado);
void comprimento(char *,char *,int), mostrar(struct dado *);
int menu(void);
//===============================================================
// Programa principal
int main(){
        system("color 0f");
        inicio=passado=NULL;
        for(;;){
            system("cls");
            switch(menu()){
                case 1:
                    system("cls");
                    inserir();
                    getchar();
                    break;

                case 2:
                    system("cls");
                    excluir(&inicio, &passado);
                    getchar();
                    break;

                case 3:
                    system("cls");
                    listar();
                    getchar();
                    break;

                case 4:
                    system("cls");
                    pesquisa();
                    getchar();
                    break;

                case 5:
                    system("cls");
                    salva();
                    getchar();
                    break;

                case 6:
                    system("cls");
                    ler();
                    getchar();
                    break;

                case 7:
                    exit(1);
                    break;
         }
      }
    }
//===============================================================
	menu(void){
        char s[80];
        int c;
        printf("\n\t\tCadastro");
        printf("\n\n\t1 - Inserir");
        printf("\n\n\t2 - Deletar");
        printf("\n\n\t3 - Listar");
        printf("\n\n\t4 - Pesquisar");
        printf("\n\n\t5 - Salvar");
        printf("\n\n\t6 - Carregar arquivo");
        printf("\n\n\t7 - SAIR\n");
        do{
            printf("\nDigite sua escolha: ");
            fflush(stdin);
            gets(s);
            c=atoi(s);
        }while(c<0||c>7);
        return c;
    }
//===============================================================
    void inserir(void){
        struct dado *info;
        int p;
        for(;;){
            info=(struct dado *)malloc(sizeof(lista));
            if(!info){
                printf("\nSem memoria");
                return;
            }
            printf("\nQuando terminar seu cadastro pressione 'ENTER'\n");
            printf("\n\n");
            fflush(stdin);
            comprimento("\tDigite o nome: ",info->nome,30);
            if(!info->nome[0]){
                break;
            }
            fflush(stdin);
            comprimento("\tDigite a rua: ", info->rua,40);
            fflush(stdin);
            comprimento("\tDigite a cidade: ",info->cidade,20);
            fflush(stdin);
            comprimento("\tDigite o estado: ",info->estado,3);
            fflush(stdin);
            comprimento("\tDigite o cep: ",info->cep,10);
            fflush(stdin);
            comprimento("\tDigite o Telefone: ",info->tel,15);
            lista_en(info, &inicio, &passado);
       }
    }
//===============================================================
/*Essa função lê uma string de comprimento máximo cont e
evita que a string seja ultrapassada. Ela também apresenta uma mendagem de aviso*/
    void comprimento(char *prompt, char *s, int cont){
        char p[255];
        do{
            printf(prompt);
            gets(p);
            if(strlen(p)>cont)
                printf("\t\tMuito longo\n");
        }while(strlen(p)>cont);
        strcpy(s, p);
    }
//===============================================================
/*Cria uma lista duplamente encadeada ordenada. */
    void lista_en( struct dado *i,struct dado **inicio, struct dado **passado){
        struct dado *velho, *p;
        if(*passado==NULL){/*primeiro elemento da lista */
            i->prox=NULL;
            i->anterior=NULL;
            *passado=i;
            *inicio=i;
            return;
        }
        p=*inicio;/*começa no topo da lista */
        velho=NULL;
        while(p){
            if(strcmp(p->nome,i->nome)<0){
                velho=p;
                p=p->prox;
            }
            else{
                if(p->anterior){
                    p->anterior->prox=i;
                    i->prox=p;
                    i->anterior=p->anterior;
                    p->anterior=i;
                    return;
                }
                i->prox=p;/*novo primeiro elemento*/
                i->anterior=NULL;
                p->anterior=i;
                *inicio=i;
                return;
            }
        }
        velho->prox=i;/*coloca no final */
        i->prox=NULL;
        i->anterior=velho;
        *passado=i;
    }
//===============================================================
    void excluir(struct dado **inicio, struct dado **passado){
        struct dado *info, *encontrar();
        char s[80];
        printf("Insira o nome: ",s, 30);
        gets(s);
        info=encontrar(s);
        if(info){
           if(*inicio==info){
              *inicio=info->prox;
              if(*inicio)(*inicio)->anterior=NULL;
              else *passado=NULL;
           }
        else{
           info->anterior->prox=info->prox;
           if(info!=*passado)
               info->prox->anterior=info->anterior;
           else
               *passado=info->anterior;
        }
        free(info);//Libera memória
        }
    }
//===============================================================
    struct dado *encontrar(char *nome){
        struct dado *info;
        info=inicio;
        while(info){
            if(!strcmp(nome, info->nome))return info;
            info=info->prox;
        }
        printf("\n\t\tNome nao encontrado.\n");
        return NULL;
    }
//===============================================================
    void listar(void){
        struct dado *info;
        info=inicio;
        if(!info){
                printf("Lista Vazia");
            }
        while(info){
            mostrar(info);
            info=info->prox;
        }
        printf("\n\n");
    }
//===============================================================
    void mostrar(struct dado *info){
            printf("\n\t\tCadastro\n\n");
            printf("\tNome: %s\n",info->nome);
            printf("\tRua: %s\n",info->rua);
            printf("\tCidade: %s\n",info->cidade);
            printf("\tEstado: %s\n",info->estado);
            printf("\tCep %s\n",info->cep);
            printf("\tTelefone %s\n",info->tel);
            printf("\n\n");
    }
//===============================================================
    void pesquisa(void){
        char nome[40];
        struct dado *info, *encontrar();
        printf("Insira o nome a procurar: ");
        gets(nome);
        info=encontrar(nome);
        if(!info)
            printf("Nao encontrado\n");
        else
            mostrar(info);
    }
//===============================================================
     void salva(void){
        struct dado *info;
        FILE *fp;
        info=inicio;
        if(!info){
                printf("Lista Vazia\n");
                return;
            }
        if((fp=fopen("Registro-Lista.txt","a+"))!=NULL){
            fprintf(fp,"\n\tNome: %s\n",info->nome);
            fprintf(fp,"\tRua: %s\n",info->rua);
            fprintf(fp,"\tCidade: %s\n",info->cidade);
            fprintf(fp,"\tEstado: %s\n",info->estado);
            fprintf(fp,"\tCep: %s\n",info->cep);
            fprintf(fp,"\tTelefone: %s\n\n",info->tel);
        }
        printf("\nSalvando arquivo\n");
        fclose(fp);
    }
//===============================================================
    void ler(void){
        struct dado *info;
        char c;
        FILE *fp;

        if((fp=fopen("Registro-Lista.txt","a+"))!= NULL){
                printf("\n\n\t CADASTRO \n");
                while( (c=fgetc(fp)) != EOF){
                       putchar(c);
                    }
            }
            else{
                printf("\n Dados indisponiveis. \n\n");
                }
            fclose(fp);
    }


