#include <iostream>
#include <vector>

using namespace std;

void test_vector();

class Vector
{
	public:
		Vector(int s):sz{s},elem{new double[s]}
		{	
			for(int i=0; i<s;i++)
				elem[i]=0;
		}
		class OutOfBoundaryEception
		{	};
	double get(int index);
	void set(int index, double e);
	double safe_get(int index);
	void safe_set(int index, double e);
	double& operator[](int index);

	~Vector()
	{
		delete[] elem;
	}
	private:
		int sz;
		double* elem;
};

double Vector::get(int index)
{
	return elem[index];
}

void Vector::set(int index,double e)
{
	elem[index]=e;
}

double Vector::safe_get(int index)
{
	if(index<0 || index >=sz)
		throw new OutOfBoundaryEception;
	return get(index);
}

void Vector::safe_set(int index,double e)
{
	if(index<0 || index >=sz)
		throw new OutOfBoundaryEception;
	set(index,e);
}

int main()
{
	test_vector();
	return 0;
}

void test_vector()
{
	int dim=10;
	Vector v{dim};

	for(int i=0; i<dim;i++)
		v.safe_set(i,i*2);

	for(int i=0; i<dim;i++)
		cout<<v.safe_get(i)<<" ";

	v[0]=1;
	v[1]=10;
	v[2]=100;
	v[3]=1000;
	v[4]=1000;

	cout<<"\n\nModifico i primi 5 elementi";
	for(int i=0; i<dim;i++)
		cout<<v[i]<<" ";

	//cout<<v.safe_get(dim+1)<<" "; //verifica eccezione
}

double& Vector::operator[](int index) //si ritorna l'indirizzo, è un po come il passaggio per riferimento in cui si passa il parametro ma solo nella fima si mette &
{
	return elem[index];
}


