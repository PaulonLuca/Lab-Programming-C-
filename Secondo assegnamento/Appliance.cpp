//Author: Luca Paulon Matricola: 1187028
#include "Component.h"
#include "Appliance.h"
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::list;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::cout;

//funzione d'inizializzazione, necessaria per iniziare a caricare i dati di un elettrodomestico noto
//l'id. Poichè i file sono ordinati per elettrodomestico, verranno quindi caricati in ordine in ordine
//di id all'inteno di una lista
void Appliance::init()
{
			vector<string> fileNames;
			ifstream file;
			try
			{
						string line="";
						file.open("models.dat");
						if(file.is_open())
						{
									while(getline(file,line))
												fileNames.push_back(line);
									file.close();
						}
						else
						{ cout<<"Unable to open the file";}
			}
			catch(...)
			{	file.close();}
				
			loadGeneral(fileNames[id-1]);	//caricamento delle informazioni generali , si mette -1 poichè gli id iniziano da 1
			loadSpecific();															//caricamento delle informazioni specifiche
}

//si caricano: il prezzo, il nome dell'elettrodomestico ed le informazioni sui componenti
//necessari, ovvero l'id, il nome del componente e la quantità necessaria per la costruzione
void Appliance::loadGeneral(string fileName)
{
		 ifstream file;
			try
			{
						string line="";
						file.open(fileName);
						if(file.is_open())
						{
								 //lettura prezzo elettrodomestico
								 getline(file,line);
								 price=atof(line.c_str());
								 //lettura nome elettrodomestico
									getline(file,line);
									vector<string>splitted=split(line,' ');
									name=splitted[1];
									//lettura informazioni generali sui componenti
									while(getline(file,line))
									{
												splitted=split(line,' ');
												Component component(atoi(splitted[0].c_str()),splitted[1],atoi(splitted[2].c_str()));
												components.push_back(component);
									}
									file.close();
						}
						else
						{ cout<<"Unable to open the file";}
			}
			catch(...)
			{	file.close();}
}

//cricamento di infomazioni specifiche sui singoli componeti: le tre fasce di prezzo ed il tempo
//impiegato ad arrivare una volta eseguito l'ordine
void Appliance::loadSpecific()
{
		 ifstream file;
			try
			{
						string line="";
						file.open("components_info.dat");
						if(file.is_open())
						{
									while(getline(file,line))
									{
												vector<string> splitted=split(line,' ');
												for(auto iter=components.begin(); iter!=components.end(); iter++)
												{
															Component& c=*iter;
															if(c.getName()==splitted[1])
															{
																		c.setMonthsNeeded(atoi(splitted[2].c_str()));
																		c.setPrice1(atof(splitted[3].c_str()));
																		c.setPrice2(atof(splitted[4].c_str()));
																		c.setPrice3(atof(splitted[5].c_str()));
															}
												}
									}
									file.close();
						}
						else
						{ cout<<"Unable to open the file";}
			}
			catch(...)
			{	file.close();}
}

//funzione che fa lo split di una stringa dato un separatore
vector<string> Appliance::split(const string& s, char delimiter)
{
   vector<string> splitted;
   string token="";
   istringstream stream(s);
   while (getline(stream, token, delimiter))
      splitted.push_back(token);
   return splitted;
}
