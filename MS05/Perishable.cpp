//Name: Serach Boes
//Date of completion: April 6, 2019

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Perishable.h"

using namespace std;

namespace ama {


	Perishable::Perishable(char type) : Product(type) {}

	std::ostream& Perishable::write(std::ostream& out, int writeMode) const{

		Product::write(out, writeMode);  //calls base class version

		if (m_expiry.isGood() && writeMode == write_human) {
			out.width(max_length_label);
			out.setf(ios::right);
			out << "Expiry Date: " << m_expiry << endl;
			out.unsetf(ios::right);
		}
		if (m_expiry.isGood() && writeMode == write_table) {
			
			out << " ";
			out.width(12); 
			out << m_expiry << " |";
		}

		if (m_expiry.isGood() && writeMode == write_condensed) {
			out << ", " << m_expiry;
		}

		return out;
	}

	std::istream& Perishable::read(std::istream& in, bool interactive) {

		Product::read(in, interactive);  //calls base class version

		Date EXPIRY;

		if (interactive == true) {   //if the second parameter is true then the function prompts the user asking for values 
			cout.width(max_length_label);
			cout.setf(ios::right);
			cout << "Expiry date (YYYY/MM/DD): ";
			in >> EXPIRY;

			if (EXPIRY.status() == error_year) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Year in Date Entry");
				return in;
			}

			if (EXPIRY.status() == error_mon) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Month in Date Entry");
				return in;
			}

			if (EXPIRY.status() == error_day) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Day in Date Entry");
				return in;
			}

			if (EXPIRY.status() == error_input) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Date Entry");
				return in;
			}
		}
		if (interactive == false) {

			in.ignore(1, ',');
			EXPIRY.read(in);
			in.ignore();
		}

		m_expiry = EXPIRY;
		return in;
	}

}