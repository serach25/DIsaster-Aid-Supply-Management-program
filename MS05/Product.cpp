//Name: Serach Boes
//Date of completion: April 6, 2019

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Product.h"

using namespace std;

namespace ama {

	void Product::message(const char* pText) {

		m_errorstate = pText;
	}

	bool Product::isClear() const {
		return (bool)m_errorstate;
	}

	Product::Product(char type) : m_type(type) {  //initialization list

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_nameOfProduct = nullptr;
		m_quantityOnHand = 0;
		m_quantityNeeded = 0;
		m_price = 0.0;
		m_taxable = true;
	}

	Product::Product(const char* SKU, const char* productName, const char* productUnit, double productPrice, int Needed, int OnHand, bool taxStatus) : m_type('N') {

		if (nullptr == productName) {
			m_sku[0] = '\0';
			m_unit[0] = '\0';
			m_nameOfProduct = nullptr;
			m_quantityOnHand = 0;
			m_quantityNeeded = 0;
			m_price = 0.0;
			m_taxable = true;
		}

		else {
			int size = 0;
			for (int i = 0; productName[i] != '\0'; ++i)
				size++;
			m_nameOfProduct = new char[size];
			for (int j = 0; j < size; ++j)
				m_nameOfProduct[j] = productName[j];
			m_nameOfProduct[size] = '\0';
			strncpy(m_sku, SKU, max_length_sku);  //strncpy(destination, source, max_length);
			strncpy(m_unit, productUnit, max_length_unit);
			m_quantityOnHand = OnHand;
			m_quantityNeeded = Needed;
			m_price = productPrice;
			m_taxable = taxStatus;
		}
	}

	Product::Product(const Product& src) : m_type('N') { //copy constructer 

		m_nameOfProduct = nullptr;
		*this = src; //calling copy assignment operator
	}



	Product::~Product() {  //destructer

		m_nameOfProduct = nullptr;  //***add this
		delete[] m_nameOfProduct;
	}


	Product& Product::operator=(const Product& src) {  //copy assignment operator

		if (this != &src) {  //checking for self-assignment
			for (int i = 0; i < max_length_sku; ++i) {  //shallow copies on all non-resource instance variables
				m_sku[i] = src.m_sku[i];
			}
			for (int j = 0; j < max_length_unit; ++j) {
				m_unit[j] = src.m_unit[j];
			}
			m_quantityOnHand = src.m_quantityOnHand;
			m_quantityNeeded = src.m_quantityNeeded;
			m_price = src.m_price;
			m_taxable = src.m_taxable;

			delete m_nameOfProduct;  //deallocate previously allocated dynamic memory
			//allocate dynamic memory for m_nameOfProduct
			if (src.m_nameOfProduct != nullptr) {
				m_nameOfProduct = new char[max_length_name];
				for (int k = 0; k < max_length_name; ++k)   //copy data from the source resource to the newly allocated resource.
					m_nameOfProduct[k] = src.m_nameOfProduct[k];

			}
			else
				m_nameOfProduct = nullptr;
		}
		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0)
			m_quantityOnHand += cnt;
		return m_quantityOnHand;

	}

	bool Product::operator==(const char* sku) const {

		bool flag = false;
		if (strcmp(m_sku, sku) == 0) {
			flag = true;
		}
		return flag;
	}

	bool Product::operator>(const char* sku) const {

		bool flag = false;
		if (strcmp(m_sku, sku) > 0) {
			flag = true;
		}
		return flag;
	}

	bool Product::operator>(const iProduct& other) const {

		bool flag = false;
		if (strcmp(m_nameOfProduct, other.name()) > 0) {
			flag = true;
		}
		return flag;
	}

	int Product::qtyAvailable() const {

		return m_quantityOnHand;

	}

	int Product::qtyNeeded() const {

		return m_quantityNeeded;

	}

	double Product::total_cost() const {

		double totalCost = 0;
		double tax = 1 + tax_rate;

		if (m_taxable == true) {   //if the product is taxable add the tax
			totalCost = (m_quantityOnHand*(m_price * tax));
		}
		else
			totalCost += (m_quantityOnHand * m_price); //if the product is not taxable don't add the tax

		return totalCost;
	}

	bool Product::isEmpty() const {  //checks if current object is in empty state

		bool flag = false;
		if (nullptr == m_nameOfProduct)
			flag = true;
		return flag;

	}

	std::istream& Product::read(std::istream& in, bool interactive) {  // reads data from the stream and stores it in the attributes

		bool TAX;
		double PRICE;
		int QTY_AVAILABLE, QTY_NEEDED;
		char UNIT[max_length_unit];
		char SKU[max_length_sku];
		char NAME[max_length_name];
		char comma;

		if (interactive == true) {   //if the second parameter is true then the function prompts the user asking for values 
			cout.width(max_length_label);
			cout.setf(ios::right);
			cout << "Sku: ";
			in >> SKU;

			cout.width(max_length_label);
			cout << "Name (no spaces): ";
			in >> NAME;

			cout.width(max_length_label);
			cout << "Unit: ";
			in >> UNIT;

			cout.width(max_length_label);
			cout << "Taxed? (y/n): ";
			char taxTemp;			
			in >> taxTemp;
			if (taxTemp == 'y' || taxTemp == 'Y') {
				TAX = 1;
			}
			else if (taxTemp == 'n' || taxTemp == 'N') {
				TAX = 0;
			}
			else {
				in.setstate(ios::failbit);
				cout << endl;
				message("Only (Y)es or (N)o are acceptable!");
				return in;
			}

			cout.width(max_length_label);
			cout << "Price: ";
			in >> PRICE;
			if (PRICE <= 0) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Price Entry!");
				return in;
			}

			cout.width(max_length_label);
			cout << "Quantity on hand: ";
			in >> QTY_AVAILABLE;
			if (QTY_AVAILABLE <= 0) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Quantity Available Entry!");
				return in;
			}

			cout.width(max_length_label);
			cout << "Quantity needed: ";
			in >> QTY_NEEDED;
			cout.unsetf(ios::right);
			if (QTY_NEEDED <= 0) {
				in.setstate(ios::failbit);
				cout << endl;
				message("Invalid Quantity Needed Entry!");
				return in;
			}
		}

		if (interactive == false)  // if the second parameter is false then , extracts all the information from the stream and doesn't interact with the user.
		{

			in.getline(SKU, max_length_sku, ',');  //because its an array of charcters need to use getline to read so it knows when to stop reading, gives length to read
			in.getline(NAME, max_length_name, ',');
			in.getline(UNIT, max_length_unit, ',');

			in >> PRICE >> comma >> TAX >> comma >> QTY_AVAILABLE >> comma >> QTY_NEEDED;

		}
		Product temp(SKU, NAME, UNIT, PRICE, QTY_NEEDED, QTY_AVAILABLE, TAX);
		*this = temp;
		return in;
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {

		if (m_errorstate) {  //if the object contains an error message, prints error message and exits
			out << m_errorstate.message();
		}

		if (!isEmpty() && writeMode == write_condensed && !m_errorstate) {  //write condensed fromat

			out << m_type << "," << m_sku << "," << m_nameOfProduct << ","
				<< m_unit << ",";
			out.precision(2);
			out.setf(ios::fixed);
			out << m_price << "," << m_taxable << ","
				<< m_quantityOnHand << "," << m_quantityNeeded;
			//out.unsetf(ios::fixed);
		}

		if (!isEmpty() && writeMode == write_table && !m_errorstate)  //write in table format
		{

			out.width(max_length_sku + 1);
			out.setf(ios::right);
			out << m_sku << " | ";
			out.unsetf(ios::right);

			int size = 0;
			for (int i = 0; m_nameOfProduct[i] != '\0'; ++i)
				size++;

			if (size > 16) {
				char tempArray[14];
				for (int j = 0; j < 13; ++j) {
					tempArray[j] = m_nameOfProduct[j];
				}
				tempArray[13] = '\0';
				out.width(13);
				out.setf(ios::left);
				out << tempArray;
				out << "...";
			}
			else if (size <= 16) {
				out.width(16);
				out.setf(ios::left);
				out << m_nameOfProduct;
			}
			out << " | ";
			out.width(10);
			out.setf(ios::left);
			out << m_unit << " | ";
			out.width(7);
			out.setf(ios::right);
			out.precision(2);
			out.setf(ios::fixed);
			out << m_price << " | ";
			//out.unsetf(ios::fixed);
			
			if (m_taxable == 1) {
				out.width(3);
				out.setf(ios::right);
				out << "yes | "; 
			}
			else {
				out.width(3);
				out.setf(ios::right);
				out << " no | ";
			}
			out.width(6);
			out << m_quantityOnHand << " | ";
			out.width(6);
			out << m_quantityNeeded << " |";
			out.unsetf(ios::right);
		}

		if (!isEmpty() && writeMode == write_human && !m_errorstate) {  //write in human format

			out.width(max_length_label);
			out.setf(ios::right);
			out << "Sku: " << m_sku << endl;

			out.width(max_length_label);
			out << "Name: " << m_nameOfProduct << endl;

			out.width(max_length_label);
			out << "Price: ";
			out.precision(2);
			out.setf(ios::fixed);
			out << m_price << endl;

			out.width(max_length_label);
			out << "Price after Tax: ";
			out.precision(2);
			if (m_taxable == 1) {
				out << m_price * (1 + tax_rate) << endl;
			}
			else if (m_taxable == 0) {
				out << m_price << endl;
			}
			//out.unsetf(ios::fixed);

			out.width(max_length_label);
			out << "Quantity Available: " << m_quantityOnHand << " " << m_unit << endl;

			out.width(max_length_label);
			out << "Quantity Needed: " << m_quantityNeeded << " " << m_unit << endl;
			out.unsetf(ios::right);
		}

		return out;
	}

	const char* Product::name() const {

		return m_nameOfProduct;
	}

}