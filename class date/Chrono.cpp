#include "Chrono.h"
#include <vector>

using namespace Chrono;
using std::cout;

namespace Chrono
{
	Date::Date(int y, Month m, int d): year{y}, month{m}, day{d} 
	{	if(!isDate(y,m,d)) throw Invalid{}; }

	//Date::Date() 
	//{ year=1970; month=Month::jan; day=1;	}
	//si può usare la lista di inizializzazione anche nel costruttore
	//di default
	Date::Date():year{1970}, month{Month::jan}, day{1} 
	{	}

	void Date::addDay(int n)
	{
		std::vector<int> days{29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		day+=n;
		int i=int(month);
		while(day>31)
		{
			if(i==2 && leapyYear(year))
				day-=days[0];
			else
				day-=days[i];
			addMonth(1);
		}
	}

	void Date::addMonth(int n)
	{
		int m=int(month)+n;
		while(m>12)
		{
			m-=12;
			addYear(1);
		}

		switch(Month(m))
		{
			case Month::jan: month=Month::jan; break;
			case Month::feb: if(leapyYear(year))
									{
										if(!(day>=1 && day<=29))
										{
											month=Month::mar;
											day-=29;
										}
										else
											month=Month::feb;
									}
									else
										{
											if(!(day>=1 && day<=28))
											{
												month=Month::mar;
												day-=28;
											}
											else
												month=Month::feb;
										} break;
			case Month::mar: month=Month::mar; break;
			case Month::apr: if(day==31){ month=Month::may; day=1; } month=Month::apr; break;
			case Month::may: month=Month::may; break;
			case Month::jun: if(day==31){ month=Month::jul; day=1; } month=Month::jun; break;
			case Month::jul: month=Month::jul; break;
			case Month::aug: month=Month::aug; break;
			case Month::sep: if(day==31){ month=Month::oct; day=1; } month=Month::sep; break;
		   case Month::oct: month=Month::oct; break;					
		   case Month::nov: if(day==31){ month=Month::dec; day=1; } month=Month::nov; break;		 
			case Month::dec: month=Month::dec; break;							
		}
	}

	void Date::addYear(int n)
	{
		if(month == Month::feb && day==29 && !leapyYear(year))
		{
			month=Month::mar;
			day=1;
		}
		year+=n;
	}

	//helper function
	bool leapyYear(int y)
	{
		if(y%400==0 || (y%4==0 && !(y%100==0)))
			return true;
		else
			return false;
	}

	bool isDate(int y, Month m, int d)
	{
		//l'anno va sempre bene
		if(d<=0 || d>31)	return false;
		if(m<Month::jan || m>Month::dec) return false;

		switch(m)
		{
			case Month::feb:  if(leapyYear(y))
									{
										if(d>=1 && d<=29)
											return true;
										else
											return false;
									}
									else
										{
											if(d>=1 && d<=28)
											return true;
										else
											return false;
										} break;
			case Month::apr: 
			case Month::jun: 
			case Month::sep: 
			case Month::nov: if(d>=1 && d<=30) 
									 return true; 
								 else 
									 return false; 
								 break;
			default: return true; break;	
		}	
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.getDay()==b.getDay() && a.getMonth()==b.getMonth() && a.getYear()==b.getYear();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a==b);
	}

	ostream& operator<<(ostream& os, const Date& a)
	{
		return os<<a.getDay()<<'/'<<int(a.getMonth())<<'/'<<a.getYear();
	}

	istream& operator>>(istream& is, Date& a)
	{
		int d,m,y;
		char ch1, ch2;
		is>>d>>ch1>>m>>ch2>>y;
		if(!is) return is;
		if(ch1!='/' && ch2!='/')
		{
			is.clear(std::ios_base::failbit);
			return is;
		}

		a=Date(y,Month(m),d);
		return is;		
	}
}

//quando compili un cpp ci deve sempre essere il main nello scope generale
int main()
{
	Date d2{2000,Month::dec,31};
	cout<<d2<<'\n';
	d2.addMonth(13);
	cout<<d2<<'\n';

	Date d3{2000,Month::feb,29};
	cout<<d3<<'\n';
	d3.addMonth(12);
	cout<<d3<<'\n';

	Date d4{2001,Month::feb,28};
	cout<<d4<<'\n';
	d4.addMonth(12);
	cout<<d4<<'\n';

	Date d5{2001,Month::jan,1};
	cout<<d5<<'\n';
	d5.addDay(31);
	cout<<d5<<'\n';

	Date d6{2003,Month::nov,29};
	cout<<d6<<'\n';
	d6.addDay(3);
	cout<<d6<<'\n';

	Date d7{2004,Month::dec,31};
	cout<<d7<<'\n';
	d7.addDay(2);
	cout<<d7<<'\n';

	if(d2!=d3) cout<<"Le prime due date sono diverse\n";

	Date d8{2004,Month::dec,31};
	Date d9{2004,Month::dec,31};
	cout<<d8<<"  "<<d9;
	if(d8==d9) cout<<"\nQueste ultime due date sono uguali";
	
	
	return 0;
}








