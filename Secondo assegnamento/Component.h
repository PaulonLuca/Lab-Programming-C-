//Author: Luca Paulon Matricola: 1187028
#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

using std::string;

class Component
{
			public:
						Component(int Id, string Name, int Qty): id{Id}, name{Name}, qty{Qty}
						{	}
						int getId() const { return id;}
						string getName() const { return name;}
						
						//metodi get e set per le fasce di prezzo e per il tempo d'arrivo
						int getMonthsNeeded() const {	return months_needed;}
						void setMonthsNeeded(int months){	months_needed=months;}
						double getPrice1() const {	return price1;}
						double getPrice2() const {	return price2;}
						double getPrice3() const {	return price3;}
						void setPrice1(double p1){	price1=p1;}
						void setPrice2(double p2){	price2=p2;}
						void setPrice3(double p3){	price3=p3;}
						int getQty() const { return qty; }
						void setQty(int Qty){ qty=Qty;}

			private:
						int id;
						string name;
						int months_needed;
						int qty;
						double price1;
						double price2;
						double price3;
};
#endif