#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Name_pairs
{
	public:
		void read_names();
		void read_ages();
		void print();
		void sort();
	private:
		vector<double> age;
		vector<string> name;
};

void Name_pairs::read_names()
{	
	string n="";
	bool finito=false;
	cout<<"Insetrisci i nomi:\n";
	while(!finito)
		{
			cin>>n;
			if(n=="0")
				finito=true;
			else
				name.push_back(n);
		}
}

void Name_pairs::read_ages()
{	
	double a=0;
	cout<<"Insetrisci le eta':\n";
	if(name.size()!=0)
		for(int i=0;i<name.size();i++)
			{
				cin>>a;
				age.push_back(a);	
			}
	else
			cout<<"Insetrisci prima i nomi!!!";
}

void Name_pairs::print() //si ha un errore di segmentazione quando si prova ad accedere alla cella di un array con indice fuori dal range
{	
	for(int i=0;i<name.size();i++)
		cout<<"Name: "<<name[i]<<" Age: "<<age[i]<<"\n";
}

void Name_pairs::sort() //bubble sort
{	
	for(int i=0;i<name.size()-1;i++)
		for(int j=0;j<name.size()-1;j++)
			if(name[j]>name[j+1])
				{
					string temp=name[j];
					name[j]=name[j+1];
					name[j+1]=temp;
					int tempAge=age[j];
					age[j]=age[j+1];
					age[j+1]=tempAge;
				}
}

int main()
{
	Name_pairs pairs;
	pairs.read_names();
	pairs.read_ages();
	cout<<"\n\nI dati inseriti non ordinati sono:\n";
	pairs.print();
	pairs.sort();
	cout<<"\n\nI dati ordinati sono:\n";
	pairs.print();
	return 0;
}
