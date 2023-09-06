#include <iostream>

using namespace std;

void f(int array[], int n);

void f(int array[], int n)
{
			cout<<"Gli elementi da stampare sono: ";
			int elements[]={10,20,30,40,50,60,70,80,90,100};
			int size=sizeof(elements)/sizeof(int);
			//int i=0;
			for(int i=0;i<size;i++)
						elements[i]=array[i];
			for(int i=0;i<size;i++)
						cout<<elements[i]<<" ";
			cout<<"\n";
			int* p=new int[n];
			delete [] p;
}

int main()
{
			int i=11;
			int array[] ={1,2,3,4,5,6,7,8,9,10};
			int j=12;
			cout<<"I valori iniziali sono: i="<<i<<"  j="<<j<<"\n";
			int* pi=&i;
			int* pj=&j;
			*pi=array[12];
			*pj=array[13];
			cout<<"I valori finali sono: i="<<i<<"  j="<<j<<"\n\n";	//con valori fuori range si ottengono valori
																																																									//non presenti nell'array
			//per calcolare la dimensione di un array locale usa:
			//sizeof(nome array)/sizeof(tipo di un elemento dell'array)
			int size=sizeof(array)/sizeof(int);
			f(array,size); 
			int aa[]={1,2,6,24,120,720,5040,40320,362880,3628800};
			size=sizeof(aa)/sizeof(int);
			f(aa,size);
}
