#include <iostream>
#include <fstream>
using namespace std;
#define MAX 100
fstream fp;
fstream fd;
struct prodotto
{
	char code[4];
	int quantity;
	float price;
	char description[50];
};
struct prodotto p[MAX];
void scrivi(fstream& f,  prodotto p[])
{char risp='n';
prodotto t;
int k=0;
do {
	cout <<"\n Digita i dati:\n";
	cout <<"\n Codice di 4 caratteri\n";
	cin.ignore(1,'\n');
	cin.getline(p[k].code,5);
	cout << "\n Digita la quantità\n";
	cin >> p[k].quantity;
	cout <<"\n Digita il prezzo\n";
	cin>>p[k].price;
	cout<<"\n Digita la Descrizione \n";
	getchar();
	cin.getline(p[k].description,30);
	f.write((char*)&p[k],sizeof(struct prodotto));
	k++;
	cout << "Altri Dati s/n ? ";
	risp=getchar();
	}
	while (risp=='s');
}
void scrivi1(fstream& f, prodotto p[])
{char risp='n';
int k=0;
prodotto temp;
long posizione=0;
int indice=0;
do {
	cout<<"\n Digita i dati:\n";
	cout<<"\n Codice di 4 caratteri \n";
	cin.ignore(1,'\n');
	cin.getline(p[k].code,5);
	cout<<"\n Digita la quantità\n";
	cin>>p[k].quantity;
	cout<<"\n Digita il prezzo\n";
	cin>>p[k].price;
	cout<<"\n Digita la Descrizione \n";
	getchar();
	cin.getline(p[k].description,30);
	do {
	cout<<"\n Inserisci indice del Record maggiore di zero\n";
	cin>>indice;
	} while (indice<=0);
	posizione=(indice-1)*sizeof(struct prodotto);
	f.seekp(posizione);
	if (f.read((char*)&temp,sizeof(struct prodotto)) && (temp.code!='\0'))
		{
		cout<<"\n Prodotto già inserito con indice %d\t"<<indice;
		cout<<"\n Inserisci un altro indice";
		cout<<"\n Ecco i dati presenti:\t Codice %s ",temp.code;
		cout<<"\n Descrizione:%s\t "<<temp.description;}
	else
		f.write((char*)&p[k],sizeof(struct prodotto));
	k++;
	cout<< "\nAltri Dati s/n ?";
	getchar();
	risp=getchar();
	}
	while (risp=='s');
}
void leggi(fstream& f,struct prodotto p[])
{	int k=0;
	int i;
	while (!f.eof())	
	{
		f.read((char*)&p[k],sizeof(struct prodotto));
		k++;
	}
	cout <<"\n Stampa a video dei dati dei prodotti\n";
	for (i=0;i<k-1;i++)
	{
		cout<<"\nCodice:\t "<<p[i].code;
		cout<<"\nDescrizione\t "<<p[i].description;
		cout<<"\nQuantità disponibile\t "<<p[i].quantity;
		cout<<"\nPrezzo del Prodotto\t" <<p[i].price;
		cout<<"\n--------\n";
	}
	cout<<"\n Stampa Terminata\n";
}
void leggi1(fstream& f,struct prodotto p[])
{
	struct prodotto temp;
	long posizione=0;
	int indice=0;
		do {
		cout<<"\n Inserisci l'indice del prodotto > 0 \n";
		cin>>indice;
		if (indice <=0)
		{
			cout<<"\n Errore nell'indice\n";
		}}
		while (indice<=0);
		posizione=(indice-1)*sizeof(struct prodotto);
		f.seekg(posizione,f.beg);
		if (f.read((char*)&temp,sizeof(struct prodotto))&&(temp.code!='\0'))
		{
			cout<<"\n Prodotto trovato\n";
			cout<<"\n Dati Prodotto:\n";
			cout<<"\n Codice:  \t "<<temp.code;
			cout<<"\n Descrizione:  \t "<<temp.description;
			cout<<"\n Prezzo:  \t "<<temp.price;
			cout<<"\n Quantità: \t "<<temp.quantity;
		}
		else
			{
			cout<<"\n Prodotto non trovato !\n";
			return; }
	}
int main (int argc, char *argv[])
{
	int scelta;
	cout<<"\n Programma per la creazione e/o gestione di un archivio di prodotti\n";
	printf("\n Effettua la tua scelta:\n");
	cout<<"\n 1- Scrittura dati nell'archivio ad accesso seqeunziale\n";
	printf("\n 2- Lettura e stampa dati proditti ad accesso sequenziale\n");
	cout<<"\n 3- Scrittura dati nell'archivio ad accesso diretto\n";
	cout<<"\n 4- Lettura nell'archivio da accesso diretto\n";
	cout<<"\n 3-  Uscita\n";
	do
	{
		cout<<"\n Effettua la tua scelta ?:\n";
		cin>>scelta;
		if ((scelta<1)&&(scelta>3))
				cout<<"\n Scelta errata! \n Effettua scelta corretta !\n";
	}
	while ((scelta<1)&&(scelta>3));
	switch (scelta)
	{
		case 1:
		{	 fp.open("archivio2.dat",ios::app | ios::binary | ios::out );
			scrivi(fp,p);
			cout<<"\n Inserimento dati Concluso\n";
			fp.close();
			break;
		}
		case 2:
		{	fp.open("archivio.dat",ios::in | ios::binary);
			leggi(fp,p);
			fp.close();
			break;
		}
		case 3:
			{
				fd.open("archivio1.dat",ios::app | ios::out | ios::binary);
				scrivi1(fd,p);
				fd.close();
				break;
			}
		case 4:
				fd.open("archivio1.dat",ios::in | ios::binary);
				leggi1(fd,p);
				fp.close();
				break;
			
	}
	return 0;
}

