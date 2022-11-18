//Name: Serach Boes
//Date of completion: April 6, 2019

#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>  // need to add #include <iostream> for the istream and ostream overloading functions

namespace ama {

	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date
	{
		int m_year;
		int m_month;
		int m_day_of_month;
		int m_status;
		void status(const int newStatus);
		int mdays(int year, int mon) const;
		void emptyState();

	public:
		Date();   // default constructer
		Date(int year, int month, int day);   //custom constructer
		int status() const;
		void clearError();
		bool isGood() const;
		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int days) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};

	std::istream& operator>>(std::istream& is, Date& d);
	std::ostream& operator<<(std::ostream& os, const Date& d);
}
#endif


