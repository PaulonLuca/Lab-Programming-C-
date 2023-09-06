//Nome: Luca	Cognome: Paulon	Matricola: 1187028

#include <iostream>
#include "Image.h"

using std::cout;
using std::cin;

void printMatr(Image im);
Image moveMatr();
Image fillMatr_at(int W, int H);
Image fillMatr_safe_at(int W, int H);
void fillMatr(Image& im);

void printMatr(Image im) 								//prova del costruttore di copia nel passaggio come parametro
{
	cout<<"Test costruttore di copia in chiamata a funzione per stampare im\n"<<im<<"OK\n\n";
}

Image moveMatr() 											//prova del costruttore spostamento
{
	int W=4;
	int H=4;
	Image im(W,H);
	fillMatr(im);
	return im;
}

Image fillMatr_at(int W, int H)
{
	Image im(W,H);
	int max=255;
	for(int i=0; i<im.getH();i++)						//indice di riga (H)
		for(int j=0; j<im.getW(); j++)			 	//indice di colonna (W)
			im.at(j,i)=rand()%max+1;		
	return im;		
}


Image fillMatr_safe_at(int W, int H)
{
	Image im(W,H);
	int max=255;
	try
	{ 
		im.safe_at(W+1,H+1)=0; 
	}
	catch(...)//con (...) funziona
	{ cout<<"Eccezione IndexOutOfBoundException gestita";	}
	
	for(int i=0; i<im.getH();i++)						//indice di riga (H)
		for(int j=0; j<im.getW(); j++)				//indice di colonna (W)
			im.safe_at(j,i)=rand()%max+1;					
	return im;		
}

void fillMatr(Image& im)
{
	int max=255;
	for(int i=0; i<im.getH();i++)						//indice di riga (H)
		for(int j=0; j<im.getW(); j++)				//indice di colonna (W)
			im.safe_at(j,i)=rand()%max+1;	
}

int main(void)
{
	//valori negativi e superiori al range [0,255] vengono automaticamente castati in un range accettato da unsigned char
	cout<<"Matrice im iniziale 3x3:\n";
	Image im(3,3);
	//test costruttore copia con chiamata a funzione
	printMatr(im);
	
	//test dei valori W e H fino a quando non sono inseriti in modo corretto
	int W=0;
	int H=0;
	bool valid=false;	
	while(!valid)
	{
		try
		{
			cout<<"Inserire W: ";
			cin>>W;
			cout<<"Inserire H: ";
			cin>>H;
			Image test(W,H);
			valid=true;	
			cout<<"Valori validi!!!\n";
		}
		catch(...)
			{ cout<<"Eccezione SizeNotValidException gestita, valori non validi!!! \n"; }
	}
	
	//test matrice passata come reference a funzione e poi riempita
	cout<<"\nMatrice im modificata con safe_at, passata esternamente:\n";
	fillMatr(im);
	cout<<im<<"\n";

	//test costruttore di copia
	cout<<"Test costruttore di copia con inizializzazione, creo im1 in cui copio im\n";
	Image im1=im;
	cout<<im1<<"OK\n\n";

	//test assegnamento di copia
	W=5; H=2;
	Image im2(W,H);
	cout<<"Matrice im2 iniziale:\n"<<im2;
	im2=im;
	cout<<"Test assegnamento di copia, creo im2 e vi assegno im\n"<<im2<<"OK\n\n";
	
	//test costruttore di spostamento
	Image im3=moveMatr();
	cout<<"Test costruttore di spostamento, creo im3\n"<<im3<<"OK\n\n";

	//test costruttore di spostamento con oggetto ritornato e popolato con at()
	W=5; H=5;
	Image im4=fillMatr_at(W,H);
	cout<<"Test at() semplice, move constructor\n"<<im4<<"OK\n\n";

	//test costruttore di spostamento con oggetto ritornato e popolato con safe_at(), e check di eccezione
	W=4; H=6;
	Image im5=fillMatr_safe_at(W,H);
	cout<<"Test safe_at(), con lacio di eccezione se si prova ad eccedere ad un pixel non valido, e move constructor\n"<<im5<<"OK\n\n";

	//test stampa immagine costante
	W=4; H=4;
	const Image im6(W,H);
	cout<<"Test stampa matrice costante\n"<<im6<<"OK\n\n";
	//im6.at(1,2)=12; //lvalue required as left operand of assignment, non si può essegnare un valore anche perchè l'oggetto è const
							//cioè non si può modificare
	
	//test conversione puntatori: da CONST a NON CONST con stampa
	W=3; H=2;
	const Image* im7=new Image(W,H);	
	Image* im8=const_cast<Image*>(im7);
	im7=nullptr;
	cout<<"Test assegnamento di copia con matrice costante, creo CONST im7, la converto in NON CONST e vi assegno i7\n"<<*im8<<"OK\n\n";
	delete im8;

	//test stampa matrice inizializzata di default, e test accesso ad elemento della matrice con nullptr
	Image im9;
	const Image im9bis;
	try
	{
		W=2; H=2;
		//unsigned char a=im9.safe_at(W,H);
		//unsigned char a=im9.at(W,H);
		//unsigned char a=im9bis.at(W,H);
		unsigned char a=im9bis.safe_at(W,H);
	}
	catch(...)
	{	cout<<"Test gestione accezione nullptr\n"<<im9<<"OK\n\n"; }
	cout<<"Test stampa matrice vuota con h=0, w=0, matr=nullptr\n"<<im9<<"OK\n\n";

	//test assegnamento di copia
	W=3; H=3;
	Image im10(W,H);
	fillMatr(im10);
	cout<<"Test assegnamento di copia, matrice im10 iniziale:\n"<<im10;
	W=2; H=2;
	im10=fillMatr_at(W,H);
	cout<<"Matrice finale dopo la move:\n"<<im10<<"OK\n\n";

	//test acesso al pixel W+1,H+1 di una matrice CONST con safe_at() const, e gestione eccezione
	int oldW=6; 
	int oldH=7;
	try
	{
		const Image im11(oldW,oldH);
		W=7; H=8;
		cout<<im11.safe_at(W,H);
	}
	catch(...)
	{ cout<<"Eccezione IndexOutOfBoundException gestita";}
	cout<<"Test stampa del pixel W+1 H+1 della matrice CONST "<<oldW<<"x"<<oldH<<" con safe_at() const\nOK\n\n";
		
	return 0;
}





