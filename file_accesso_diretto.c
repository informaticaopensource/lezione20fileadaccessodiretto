#include <stdio.h>
#define MAX 100
FILE *fp;
FILE *fd;
struct prodotto
{
	char code[4];
	int quantity;
	float price;
	char description[50];
};
struct prodotto p[MAX];
void scrivi(FILE *f, struct prodotto p[])
{char risp='n';
int k=0;
do {
	printf("\n Digita i dati:\n");
	printf("\n Codice di 4 caratteri\n");
	getchar();
	gets(p[k].code);
	printf("\n Digita la quantità\n");
	scanf("%d",&p[k].quantity);
	printf("\n Digita il prezzo\n");
	scanf("%f",&p[k].price);
	printf("\n Digita la Descrizione \n");
	getchar();
	gets(p[k].description);
	fwrite(&p[k],sizeof(struct prodotto),1,f);
	k++;
	printf("Altri Dati s/n ?");
	scanf("%c",&risp);
	}
	while (risp=='s');
}
void scrivi1(FILE *f, struct prodotto p[])
{char risp='n';
int k=0;
struct prodotto temp;
long posizione=0;
int indice=0;
do {
	printf("\n Digita i dati:\n");
	printf("\n Codice di 4 caratteri\n");
	getchar();
	gets(p[k].code);
	printf("\n Digita la quantità\n");
	scanf("%d",&p[k].quantity);
	printf("\n Digita il prezzo\n");
	scanf("%f",&p[k].price);
	printf("\n Digita la Descrizione \n");
	getchar();
	gets(p[k].description);
	do {
	printf("\n Inserisci indice del Record maggiore di zero\n");
	scanf("%d",&indice);
	} while (indice<=0);
	posizione=(indice-1)*sizeof(struct prodotto);
	fseek(fd,posizione,0);
	if (fread(&temp,sizeof(struct prodotto),1,fd) && (temp.code!='\0'))
		{
		printf("\n Prodotto già inserito con indice %d\t",indice);
		printf("\n Inserisci un altro indice");
		printf("\n Ecco i dati presenti:\t Codice %s ",temp.code);
		printf("\n Descrizione:%s\t ",temp.description);}
	else
		fwrite(&p[k],sizeof(struct prodotto),1,f);
	k++;
	printf("Altri Dati s/n ?");
	getchar();
	scanf("%c",&risp);
	}
	while (risp=='s');
}
void leggi(FILE *f,struct prodotto p[])
{	int k=0;
	int i;
	while (!feof(fp))	
	{
		fread(&p[k],sizeof(struct prodotto),1,f);
		k++;
	}
	printf("\n Stampa a video dei dati dei prodotti\n");
	for (i=0;i<k-1;i++)
	{
		printf("\nCodice:\t %s",p[i].code);
		printf("\nDescrizione\t %s",p[i].description);
		printf("\nQuantità disponibile\t %d",p[i].quantity);
		printf("\nPrezzo del Prodotto\t %f",p[i].price);
		printf("\n--------\n");
	}
	printf("\n Stampa Terminata\n");
}
void leggi1(FILE *f,struct prodotto p[])
{
	struct prodotto temp;
	long posizione=0;
	int indice=0;
		do {
		printf("\n Inserisci l'indice del prodotto > 0 \n");
		scanf("%d",&indice);
		if (indice <=0)
		{
			printf("\n Errore nell'indice\n");
		}}
		while (indice<=0);
		posizione=(indice-1)*sizeof(struct prodotto);
		fseek(fd,posizione,0);
		if (fread(&temp,sizeof(struct prodotto),1,f)&&(temp.code!='\0'))
		{
			printf("\n Prodotto trovato\n");
			printf("\n Dati Prodotto:\n");
			printf("\n Codice:  \t %s",temp.code);
			printf("\n Descrizione:  \t %s",temp.description);
			printf("\n Prezzo:  \t %f",temp.price);
			printf("\n Quantità: \t %d",temp.quantity);
		}
		else
			{
			printf("\n Prodotto non trovato !\n");
			return; }
	}
int main (int argc, char *argv[])
{
	int scelta;
	printf("\n Programma per la creazione e/o gestione di un archivio di prodotti\n");
	printf("\n Effettua la tua scelta:\n");
	printf("\n 1- Scrittura dati nell'archivio ad accesso seqeunziale\n");
	printf("\n 2- Lettura e stampa dati proditti ad accesso sequenziale\n");
	printf("\n 3- Scrittura dati nell'archivio ad accesso diretto\n");
	printf("\n 4- Lettura nell'archivio da accesso diretto\n");
	printf("\n 3-  Uscita\n");
	do
	{
		printf("\n Effettua la tua scelta ?:\n");
		scanf("%d",&scelta);
		if ((scelta<1)&&(scelta>3))
				printf("\n Scelta errata! \n Effettua scelta corretta !\n");
	}
	while ((scelta<1)&&(scelta>3));
	switch (scelta)
	{
		case 1:
		{	fp=fopen("archivio.dat","a+b");
			scrivi(fp,p);
			printf("\n Inserimento dati Concluso\n");
			fclose(fp);
			break;
		}
		case 2:
		{
			fp=fopen("archivio.dat","rb");
			leggi(fp,p);
			fclose(fp);
			break;
		}
		case 3:
			{
				fd=fopen("archivio1.dat","a+b");
				scrivi1(fd,p);
				fclose(fd);
				break;
			}
		case 4:
				fd=fopen("archivio1.dat","rb");
				leggi1(fd,p);
				fclose(fd);
				break;
			
	}
	return 0;
}

