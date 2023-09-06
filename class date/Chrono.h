#include <iostream>

using std::ostream;
using std::istream;

namespace Chrono
{
	enum class Month
	{
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date
	{
		public:
		class Invalid{	}; 							 //oggetto da lanciare per gestire le eccezioni
		Date();
		Date(int y, Month m, int d);
		int getDay() const {	return day;	}; 		 //funzione inline
		Month getMonth() const { return month;	};  //funzione inline
		int getYear() const { return year; }; 		 //funzione inline
		void addDay(int n);
		void addMonth(int n);
		void addYear(int n);

		private:
		int day;
		Month month;
		int year;
	};

	bool leapyYear(int y);
	bool isDate(int y, Month m, int d);
	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	ostream& operator<<(ostream& os, const Date& a);
	istream& operator>>(istream& is, Date& a);

	enum class Day
	{
		monday=1,tuesday, wednesday, thursday, friday, saturday, sunday
	};

	Day day_of_week(const Date& d);
	Date next_Sunday(const Date& d);
	Date next_weekday(const Date& d);
}








