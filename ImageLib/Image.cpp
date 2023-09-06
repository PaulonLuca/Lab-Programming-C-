//Nome: Luca	Cognome: Paulon	Matricola: 1187028

#include <iostream>
#include "Image.h"

using std::ostream;//non importo tutta la libreria standard ma solo ciò che serve

//inizializzo a valori di default
Image::Image()	
{	
	h=0;
	w=0;
	matr=nullptr;
}

//controlla la dimensione dell'immagine
bool Image::validSize(int W, int H)
{	
	if(W<=0 || H<=0)
		return false;
	return true;
}

//w e h sono uguali a W e H (non si è usata la lista di inizializzazione poichè non si poteva fare il controllo dei dati inizializzati)
Image::Image(int W, int H)
{	
	if(!validSize(W,H))
		throw new SizeNotValidException();
	h=H; 
	w=W;
	matr=new unsigned char[W*H];

	for(int i=0;i<(w*h);i++)
		matr[i]=0;
}

//costruttore di copia
Image::Image(const Image& im):h{im.h},w{im.w}, matr{new unsigned char[im.w*im.h]}
{	
	copy(im.matr,im.matr+(w*h),matr);
}

//assegnamento di copia
Image& Image::operator=(const Image& im)
{
	unsigned char* new_matr=new unsigned char[im.h*im.w];
	copy(im.matr,im.matr+(im.w*im.h),new_matr);
	delete [] matr;
	h=im.h;
	w=im.w;
	matr=new_matr;
	return *this;
}

//costruttore di spostamento
Image::Image(Image&& im): h{im.h}, w{im.w}, matr{im.matr}
{
	im.h=0;
	im.w=0;
	im.matr=nullptr;
}

//assegnamento di spostamento
Image& Image::operator=(Image&& im)
{
	delete [] matr;
	h=im.h;
	w=im.w;
	matr=im.matr;
	im.h=0;
	im.w=0;
	im.matr=nullptr;
	return *this;
}

//ritorna il riferimento al pixel [H][W]
unsigned char& Image::at(int W, int H)
{
	return matr[w*H+W];//ampiezza riga: w, indice di riga: H, indice di colonna: W
}

//ritorna il pixel [H][W]
unsigned char Image::at(int W, int H) const
{
	return matr[w*H+W];//ampiezza riga: w, indice di riga: H, indice di colonna: W
}

//controlla se gli indici rientrano nei range
bool Image::validIndexes(int W, int H) const
{
	if((W>=0 && W<w)&&(H>=0 && H<h))
		return true;
	return false;
}

//ritorna il riferimento al pixel [H][W], controllando che
//gli indici siano nei range prestabiliti,
//non è permesso l'accesso a matrici con puntatore nullo
unsigned char& Image::safe_at(int W, int H)
{
	if(matr)
	{
		if(!validIndexes(W,H))
			throw new IndexOutOfBoundException();
	}	
	else
		throw new NullPointerException();
	return at(W,H);
}

//ritorna il pixel [H][W], controllando che
//gli indici siano nei range prestabiliti
//non è permesso l'accesso a matrici con puntatore nullo
unsigned char Image::safe_at(int W, int H) const 
{
	if(matr)
	{
		if(!validIndexes(W,H))
			throw new IndexOutOfBoundException();
	}	
	else
		throw new NullPointerException();
	return at(W,H);
}

//overloading dell'operatore <<
ostream& operator<<(ostream& os, const Image& im)
{
	int h=im.getH();
	int w=im.getW();
	unsigned char* matr=im.getMatr();

	for(int i=0; i<h;i++)
	{
		for(int j=0; j<w; j++)
			os<<static_cast<unsigned int>(matr[i*w+j])<<" ";
		os<<"\n";
	}
	return os;
}


