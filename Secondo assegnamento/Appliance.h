//Author: Luca Paulon Matricola: 1187028
#ifndef APPLIANCE_H
#define APPLIANCE_H
#include "Component.h"
#include <list>
#include <string>
#include <vector>

using std::string;
using std::list;
using std::vector;

class Appliance
{
			public:
						Appliance(int Id)		//noto l'id è possibile creare un'elettrodomestico
						{	id=Id; init(); }
						int getId() const { return id;}
						string getName() const { return name;}
						list<Component>::const_iterator getIterator(){	return components.begin(); }
						int numComponets(){ return components.size();}
						double getPrice() const { return price;}
			private:
						int id;
						string name;
						list<Component> components;
						double price;

						void init();
						void loadGeneral(string fileName);
						void loadSpecific();
						vector<string> split(const string& s, char delimiter);
};
#endif
