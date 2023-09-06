#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//le strutture o comunque i vari tipi di dato vanno definiti prima della dischiarazione delle funzioni
struct MaxMin
{
	int max;
	int min;
};

void print(string s,vector<int>& v);
void fibonacci(int x, int y, int n, vector<int>& v1);
double fibonacci(int x, int y,double max);
vector<int> reverse1(vector<int> v2);
void reverse2(vector<int>& v2);
MaxMin maxv(vector<int> v3);



//è possibile ridichiarare un'array? cioè usare la stessa variabile per puntare ad un nuovo array?

int main (void)
{
	//esercizio 2
	vector<int> v {1,2,3,4,5,6,7,8,9,10};
	print("Print array: ",v);

	//esercizio 3
	int n=10;
	vector<int> v1(n);
	fibonacci(1,2,n,v1);
	print("\nFibonacci: ",v1);

	//esercizio 4
	double max=pow(2,31)-1;
	cout<<"\nArrotondamento di 2^32: "<<max<<" con fibonacci: "<<fibonacci(1,2,max)<<"\n";

	//esercizio 5
	vector<int> v2={1,3,5,7,9,0};
	print("\nArray originale: ", v2);
	vector<int> v3=reverse1(v2);
	print("Reverse 1: ", v3);
	reverse2(v2);
	print("Reverse 2: ", v2);
	
	//esercizio 11: preferisco usare un nuovo tipo di dato come una struct poichè si ha un solo oggetto da gestire al posto di più
	//puntatori o alias che potrebbero essere ambigui
	vector<int> v4={5,7,8,9,3,56,45,12,34,56,11,33,88,71,32};
	print("\nArray in cui cercare: ", v4);
	MaxMin numeri=maxv(v4);
	cout<<"Max: "<<numeri.max<<"  Min: "<<numeri.min<<"\n";
	return 0;
}

void print (string s, vector<int>& v)
{
	cout<<s;
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<"\n";
}

void fibonacci(int x, int y, int n, vector<int>& v1)//se passo array vuoto posso usare la stessa variabile per crearne uno nuovo??
{
	int primo=x;
	int secondo=y;
	int terzo=0;
	v1[0]=primo;
	v1[1]=secondo;
	for(int i=2; i<n; i++)
	{
		terzo=primo+secondo;
		v1[i]=terzo;
		primo=secondo;
		secondo=terzo;
	}
}

double fibonacci(int x, int y, double max)
{
	double primo=x;
	double secondo=y;
	double terzo=0;
	double temp=0;

	while(temp<max)
	{
		temp=primo+secondo;
		if(temp<max)
		{
			terzo=primo+secondo;
			primo=secondo;
			secondo=terzo;
		}
	}
	return terzo;
}

vector<int> reverse1(vector<int> v2)
{
	vector<int> v(v2.size());
	int j=0;
	for(int i=v2.size()-1;i>=0;i--)
		v[j++]=v2[i];
	return v;
}

void reverse2(vector<int>& v2)
{
	for(int i=0; i<v2.size()/2; i++)
	{
		//senza puntatori
		/*int temp=v2[v2.size()-i-1];
		v2[v2.size()-i-1]=v2[i];
		v2[i]=temp;*/
		
		//con puntatori
		int& elem=v2[v2.size()-i-1];
		int temp=elem;
		elem=v2[i];
		v2[i]=temp;
	}
}

MaxMin maxv(vector<int> v3)
{
	int max=v3[0];
	int min=v3[0];

	for(int i=1;i<v3.size();i++)
		if(v3[i]>max)
			max=v3[i];

	for(int i=1;i<v3.size();i++)
		if(v3[i]<min)
			min=v3[i];

	MaxMin numeri;
	numeri.max=max;
	numeri.min=min;

	return numeri;
}


