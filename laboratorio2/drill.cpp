#include <iostream>
#include <vector>

using namespace std;

void print_array10(ostream& os, int* a);

int main()
{
	int* p= new int[10]{0,1,2,3,4,5,6,7,8,9};
 	for(int i=0; i<10; i++)
  	cout<<p[i]<<" "; //metti lo spazio altimenti non concatena nulla
 	cout<<"\n";

 	delete[] p;

 	int* p1= new int[10]{1,2,4,8,16,32,64,128,256,512};
 	int* p2= new int[10];
 	for(int i=0;i<10;i++)
  		p2[i]=p1[i];
 	print_array10(cout, p2);

 vector<int> v1{1,2,4,8,16,32,64,128,256,512};
 vector<int> v2(10);
 for(int i=0;i<10;i++)
  v2[i]=v1[i];
 
 	return 0;
}

void print_array10(ostream& os, int* a)
{
	for(int i=0; i<10; i++)
  		os<<a[i]<<" ";
 	os<<"\n";
}
