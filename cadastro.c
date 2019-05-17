// Mateus Guedes da Conceição - 2215202730

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct pasta
{
       char nome[40];
       int codigo;
       struct pasta*proximo;
       struct pasta*anterior;
       };


struct pasta *inicio,*ultimo;
int loaded = 0; // flag para arquivo
int lastcode = 0;
int menu();
void listaligada(struct pasta*);
void cadastro();
void alterar();
void exclui();
void lista();
void gravar();
void abrir();
void ordenar();
//------------------------------------------------------------------------------
int main()
{

             int i;
             inicio = ultimo = NULL;
             for(;;)
             {
             i=menu();

             switch(i)
            {  case 1: cadastro();
               break;

               case 2: alterar();
               break;

               case 3: exclui();
               break;

               case 4: lista();
               break;

               case 5: gravar();
               break;

               case 6: abrir();
               break;

               case 7: ordenar();
               break;

               case 8: exit(0);
               }//switch
               }//for

               return 0;
}//main

int menu()
{ int i;
system("cls");
printf("\n\t\t MENU \n\n");
printf("\t 1 - Cadastro \n");
printf("\t 2 - Alterar \n");
printf("\t 3 - Excluir \n");
printf("\t 4 - Lista \n");
printf("\t 5 - Gravar \n");
printf("\t 6 - Abrir \n");
printf("\t 7 - Ordenar \n");
printf("\t 8 - SAIR \n");

printf("\n \tEntre com a opcao:");
scanf("%d", &i);
return i;
}//menu


void cadastro()
{
     static int i = 0;
     struct pasta *p;

     if(loaded) {
     	i = ultimo->codigo;
     	loaded = 0;
     }
     if(lastcode){
        i = lastcode;
        lastcode = 0;
     }

     system("cls");
     printf("\n\t\t CADASTRO \n");
     printf("\t Tecle Apenas Enter Para Sair \n");
     for(;;){
             printf("\n Nome %d:",i+1);
             fflush(stdin);
             p=(struct pasta*) malloc (sizeof(struct pasta));
             gets(p->nome);
             if(!p->nome[0])
             break;
             p->codigo=++i;
             listaligada(p);
             }
}

int pegarQtd(){
    struct pasta *p;
    p = inicio;

    int q = 0;

    while(p != NULL){
            p = p->proximo;
            q++;
    }

    return q;
}



void ordenar(){
	 struct pasta *p;
	 p = inicio;
	 int q, i;
	 char temp[40];
	 int tempc;

	 system("cls");
	 printf("\t\t ORDENAR \n\n");

	 if(p == NULL || pegarQtd() < 2){
	 	printf("Sem registros para ordenar.\n");
	 	system("pause");
		return;
     }

     printf("Ordenando %i registros...", pegarQtd());
     q = pegarQtd();

       for(i=0; i < q; i++){
		 while(p->proximo != NULL){
			 if(strcmp(p->nome,p->proximo->nome) > 0)
			    {
                   strcpy(temp,p->nome);
                   tempc = p->codigo;
				   strcpy(p->nome,p->proximo->nome);
				   p->codigo = p->proximo->codigo;
				   strcpy(p->proximo->nome,temp);
				   p->proximo->codigo = tempc;
				   strcpy(temp,p->nome);

                  if(p->codigo >= lastcode)
                    lastcode = p->codigo;
				}
			p = p->proximo;


        }
        p = inicio;
    }
	  printf("Feito. \nFavor ir ate a lista para verificar alteracoes.\n");
      system("pause");
}

void alterar(){
	 struct pasta *p;
	 int codigo;
	 p = inicio;

	 system("cls");
	 printf("\t\t ALTERAR \n\n");

	 if(p == NULL){
	 	printf("Sem registros para alterar.\n");
	 	system("pause");
	    return;
     }

	 printf("\t\t Especifique o codigo: ");
	 scanf("%d",&codigo);

	 if(codigo > 0){
		for(;;){
			if(p->codigo == codigo){
			 	printf("\nEncontrado registro:");
		        printf("\n Nome: %s",p->nome);
		        printf("\n Codigo: %d",p->codigo);
		        printf("\nDe um novo nome: ");
		        fflush(stdin);
		        gets(p->nome);
		        printf("\nSalvo.");
				break;
		    }
			else if(p->proximo != NULL)
		 		p = p->proximo;
		 	else{
		 		printf("Registro nao encontrado.");
		 		break;
				 }

		 }
	}else
		printf("Especifique um codigo valido.");

	 printf("\n");
	 system("pause");
}

void gravar(){
	FILE *file;
	char nome[30];
	struct pasta *p;
	size_t size;

	p = inicio;


	if(p != NULL)
		{
			system("cls");
			printf("\t\t GRAVAR ARQUIVO \n\n");
	 		printf("\t\t Salvar como: ");
			fflush(stdin);
			gets(nome);
			if(!nome[0])
					return;

			strcat(nome, ".dat");
			file = fopen(nome, "wb");
			while(p != NULL)
			{
				fwrite(p, sizeof(struct pasta), 1, file);
				p = p->proximo;
			}
			size = ftell(file);

			printf("%s salvo. \nSalvo %i registros em %i bytes.\n", nome, ultimo->codigo, size);
		}else
			printf("Nao ha registros a serem salvos.\n");

	free(p);
	fclose(file);
	system("pause");
}


void abrir(){
	FILE *file;
	char nome[30];
	struct pasta *p, temp;

	system("cls");
	printf("\t\t ABRIR ARQUIVO \n\n");
	printf("\t\t Nome do arquivo: ");
	fflush(stdin);
	gets(nome);

	if(!nome[0])
		return;

	strcat(nome, ".dat");
	file = fopen(nome, "rb");

	if(file == NULL){
		printf("\n\n%s - Arquivo nao encontrado.\n", nome);
		system("pause");
		return;
		}

	p = inicio;
    free(p);


	while(fread(&temp, sizeof(struct pasta), 1, file)){
		p = (struct pasta*)malloc(sizeof(struct pasta)); // alocar 64 bytes a cada leitura (1 struct)

        p->codigo = temp.codigo;

		strcpy(p->nome, temp.nome);
		listaligada(p);
	}
	loaded = 1; // flag para funcao cadastro();

	printf("\n\n%s carregado com sucesso.\n", nome);


	system("pause");
	fclose(file);

}

//------------------------------------------------------------------------------

void exclui()
{
 struct pasta *p;
 int codigo;
 system("cls");
 printf("\t\t EXCLUIR \n\n");
 printf("\t\t Entre Com Um Codigo: ");
 scanf("%d",&codigo);

 p=inicio; //Preparando-Se Para Buscar

 while(p!=NULL)
 {
  if(p->codigo==codigo)
  { //Se Entrar Aqui Achou
     if(p->anterior==NULL)
     { //entao eh o primeiro registro
        if(p->proximo==NULL)
        {  inicio=ultimo=NULL;
           free(p);
           break;
         }
          else{
                inicio=p->proximo;
                 inicio->anterior=NULL;
                 free(p);
               }

        } //entao eh o ultimo
         else if(p->proximo==NULL)  {
                ultimo=p->anterior;
                ultimo->proximo=NULL;
                free(p);
                break;
               } else { //entao eh um do meio
                        p->anterior->proximo=p->proximo;
                        p->proximo->anterior=p->anterior;
                        free(p);
                         break;
                         }
      }

      p=p->proximo;
   }//while

 if(p==NULL)
 printf("\n %d Nao Localizado \n",codigo);
 else printf("\n Sucesso \n");
 system("pause") ;
} //Excluir

//------------------------------------------------------------------------------

void listaligada (struct pasta *p)
{
     if (inicio==NULL){
                       inicio=ultimo=p;
                       p->proximo=NULL;
                       p->anterior=NULL;
                       return;
                       }
     ultimo->proximo=p;
     p->anterior=ultimo;
     p->proximo=NULL;
     ultimo=p;
}//listaligada
//------------------------------------------------------------------------------



void lista()
{
     struct pasta *p;
     system("cls");
     printf("\n\t\t LISTA \n");
     p=inicio;
     while(p!=NULL){
                    printf("\n %s",p->nome);
                    printf("\n codigo: %d",p->codigo);
                    p=p->proximo;
                    printf("\n---------------------------\n");
                    }
     system("pause");
}//lista