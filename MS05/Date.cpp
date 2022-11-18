//Name: Serach Boes
//Date of completion: April 6, 2019

#include <iostream>
#include "Date.h"
using namespace std;

namespace ama
{

	void Date::emptyState() {  // function sets object to an empty state without changing the error status

		m_year = 0;
		m_month = 0;
		m_day_of_month = 0;
	}

	Date::Date() {    // default constructer sets object to an empty state

		m_year = 0;
		m_month = 0;
		m_day_of_month = 0;
		m_status = 0;
	}

	Date::Date(int year, int month, int day) {  //custom constructer with 3 parameters
		int days = mdays(year, month);

		if ((year >= min_year && year <= max_year) &&  // if input date is valid set current object to values of parameter
			(month >= 1 && month <= 12) &&
			(day >= 1 && day <= days))
		{
			m_year = year;
			m_month = month;
			m_day_of_month = day;
			m_status = no_error;
		}

		else if (year < min_year || year > max_year) {  // if year is not valid set error in year
			status(error_year);
			emptyState();
		}

		else if (month < 1 || month > 12) { // if month is not valid set error in month
			status(error_mon);
			emptyState();
		}

		else if (day < 1 || day > days) { // if day is not valid set error in day
			status(error_day);
			emptyState();
		}
	}

	void Date::status(int newStatus) {  //set status
		m_status = newStatus;
	}

	int Date::mdays(int year, int mon) const {  //check total amount of valid days in a specific month

		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	int Date::status() const {   //tells us the status of an object

		return m_status;
	}

	void Date::clearError() {   // sets the error status back to no error
		m_status = no_error;
	}

	bool Date::isGood() const {  // checks if a date is valid. returns true if valid date


		int days = mdays(m_year, m_month);
		if ((m_year >= min_year && m_year <= max_year) &&
			(m_month >= 1 && m_month <= 12) &&
			(m_day_of_month >= 1 && m_day_of_month <= days) &&
			m_status == no_error) {
			return true;
		}
		else {
			return false;
		}
	}

	Date& Date::operator+=(int days)
	{
		int total = m_day_of_month + days;

		if (!isGood())  //call the isGood function for validation
		{
			status(error_invalid_operation);
		}
		else if (total > mdays(m_year, m_month) || total < 1)

		{
			status(error_invalid_operation);
		}
		else
			m_day_of_month = total;
		return *this;
	}


	Date& Date::operator++() {  //prefix

		*this += 1;
		return *this;  // returning the updated current instance //why it can return by reference and postfix cannot
	}

	Date Date::operator++(int) {  //postfix

		Date copy = *this;  // saving the original
		*this += 1;
		return copy;    //return the original before it gets updated
	}

	Date Date::operator+(int days) const {

		Date temp = *this;
		temp += days;
		return temp;
	}

	bool Date::operator==(const Date& rhs) const { //checking if 2 dates are the same, if they are returns true

		Date date = *this;
		bool ret = false;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month == rhs.m_day_of_month)
			ret = true;
		return ret;

	}
	bool Date::operator!=(const Date& rhs) const { //checking if 2 dates are different, if they are returns false

		Date date = *this;
		bool ret = false;
		if (date.m_year != rhs.m_year || date.m_month != rhs.m_month || date.m_day_of_month != rhs.m_day_of_month)
			ret = true;
		return ret;
	}

	bool Date::operator<(const Date& rhs) const {

		Date date = *this;
		bool ret = false;
		if (date.m_year < rhs.m_year)
			ret = true;
		else if (date.m_year == rhs.m_year && date.m_month < rhs.m_month)
			ret = true;
		else if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month < rhs.m_day_of_month)
			ret = true;
		return ret;
	}

	bool Date::operator>(const Date& rhs) const {

		Date date = *this;
		bool ret = false;
		if (date.m_year > rhs.m_year)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month > rhs.m_month)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month > rhs.m_day_of_month)
			ret = true;
		return ret;
	}

	bool Date::operator<=(const Date& rhs) const {

		Date date = *this;
		bool ret = false;
		if (date.m_year < rhs.m_year)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month < rhs.m_month)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month < rhs.m_day_of_month)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month == rhs.m_day_of_month)
			ret = true;
		return ret;
	}

	bool Date::operator>=(const Date& rhs) const
	{
		Date date = *this;
		bool ret = false;
		if (date.m_year > rhs.m_year)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month > rhs.m_month)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month > rhs.m_day_of_month)
			ret = true;
		if (date.m_year == rhs.m_year && date.m_month == rhs.m_month && date.m_day_of_month == rhs.m_day_of_month)
			ret = true;
		return ret;
	}

	std::istream& Date::read(std::istream& is) {

		int year, month, day;
		char space;
		//is.clear();
		is >> year >> space >> month >> space >> day;
		//is >> year;
		//is >> month;
		//is >> day;

		if (is.fail()) {
			*this = Date();
			status(error_input);
		}

		else
			*this = Date(year, month, day);
		return is;
	}

	std::ostream& Date::write(std::ostream& os) const {

		char symbol = '/';
		os.fill('0');
		os.width(4);
		os << m_year << symbol;

		os.width(2);
		os.unsetf(ios::left);
		os.fill('0');
		os << m_month << symbol;

		os.width(2);
		os.unsetf(ios::left);
		os.fill('0');
		os << m_day_of_month;

		os.fill(' ');

		return os;
	}

	//Helper functions
	std::istream& operator>>(std::istream& is, Date& d) {

		return d.read(is);

	}
	std::ostream& operator<<(std::ostream& os, const Date& d) {

		return d.write(os);

	}

}