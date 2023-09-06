//Nome: Luca	Cognome: Paulon	Matricola: 1187028

#include <iostream>

using std::ostream;
using std::copy;

class Image
{
	/*
		Condizioni invarianti:
		- W e H intesi come indici ai pixel devono essere rispettivamente compresi negli intevalli: W:[0,w[ e H:[0,h[
		- W e H intesi come valori delle dimensioni della matrice devono stare nei seguenti intevalli: W]0,+inf[ e H]0,+inf[
		  (con +inf si intende il limite superiore della dimensione di un int, poichè W e H sono memorizzate in un intero)
		- non si può accedere ai pixel delle immagini con puntatori nulli (ne è invece permessa la copia) 
	*/

	public:
		class IndexOutOfBoundException{	};					//eccezione per controllare i range delle coordinate ai pixel
		class SizeNotValidException{	};						//eccezione per controllare la dimensione dell'immagine
		class NullPointerException{	};						//eccezione per avvertire che si sta cercando di accedere ad una immagine con nullptr

		Image();														//costruttore di default
		Image(int W, int H);										//costruttore con due parametri, W=width H=height
		Image(const Image& im);									//costruttore di copia
		Image(Image&& im); 										//costruttore di spostamento
		Image& operator=(const Image& im);					//assegamento di copia
		Image& operator=(Image&& im);							//assegnamento di spostamento
		unsigned char& at(int W,int H);						//ritorna il riferimento al pixel [W][H]
		unsigned char at(int W,int H) const;				//ritorna il pixel [W][H]
		unsigned char& safe_at(int W,int H);				//ritorna il riferimento al pixel [W][H], controllando le condizioni invarianti sugli indici
		unsigned char safe_at(int W,int H) const;			//ritorna il pixel [W][H], controllando le condizioni invarianti sugli indici

		int getH() const { return h; }						//i 3 metodi get a lato servono per accedere ai dati membro nell'overloading				 
		int getW() const { return w; } 						//dell'operatore, poichè ridefinito fuori dalla classe
		unsigned char* getMatr() const { return matr; }	

		~Image(){ delete [] matr; }							//distruttore, dealloco la memoria

	private:
		int h;														//altezza dell'immagine
		int w;														//larghezza dell'immagine
		unsigned char* matr;										//puntatore all'immagine in memoria
		bool validSize(int W, int H);							//controlla se la dimensione dell'immagine è un valore >0
		bool validIndexes(int W, int H) const;				//controllo di validità delle condizioni invarianti dei range degli indici:
																		//definita const poichè viene utilizzata anche nella versione safe_at() const
																		//devo dare garanzia al compilatore che tale funzione poichè invocata in un
																		//una funzione const non modifichi l'oggetto
};

ostream& operator<<(ostream& os, const Image& im);		//overloading dell'operatore <<








