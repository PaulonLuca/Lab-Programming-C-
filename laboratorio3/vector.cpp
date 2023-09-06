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
		Vector()
		{
			//Vector(10);<---si può fare??
			sz=10;
			elem=new double[sz];
			num_elem=0;		
		}
		class OutOfBoundaryEception
		{	};
	double get(int index);
	void set(int index, double e);
	double safe_get(int index);
	void safe_set(int index, double e);
	double& operator[](int index);
	void push_back(double e);
	double* trim(int n);
	int size(){	return sz; }

	~Vector()
	{
		delete[] elem;
	}
	private:
		int sz;
		double* elem;
		int num_elem;
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

double& Vector::operator[](int index)
{
	return elem[index];
}

void Vector::push_back(double e)
{
	if(sz==(num_elem+1))
	{
		double* new_elem=new double[sz*2];
		for(int i=0;i<sz;i++)
			new_elem[i]=elem[i];
		delete [] elem;
		elem=new_elem;
		sz=sz*2;
	}
	elem[num_elem++]=e;
}

double* Vector::trim(int n)
{
	int dim=0;
	if(n>=num_elem)
		dim=num_elem;
	else
		dim=n;
	double* trim_elem=new double[dim];
	for(int i=0;i<dim;i++)
		trim_elem[i]=elem[i];
	delete [] elem;
	elem=trim_elem;
	sz=dim;
	num_elem=dim;	
}

int main()
{
	test_vector();
	return 0;
}

void test_vector()
{
	Vector v1;
	int num_elem=12;
	for(int i=0; i<num_elem;i++)
		v1.push_back(i);
	cout<<"I valori inseriti sono: ";
	for(int i=0; i<v1.size();i++)
		cout<<v1.safe_get(i)<<" ";
	cout<<"\nPrima di chiamare trim la dimesione è: "<<v1.size();
	v1.trim(15);
	cout<<"\nDopo aver chiamato trim la dimesione è: "<<v1.size();
	cout<<'\n';
}



