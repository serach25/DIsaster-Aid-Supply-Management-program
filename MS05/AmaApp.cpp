//Name: Serach Boes
//Date of completion: April 6, 2019

#include <iostream>
#include <cstring>  
#include <fstream>
#include "AmaApp.h"
#include "Sort.h"
using namespace std;
 
namespace ama
{
	AmaApp::AmaApp(const char* filename) {  //custom constructer

		if (nullptr != filename && filename[0] != '\0') {   //copy filename parameter to m_filenmae if not empty and not = to nullptr 
			strcpy(m_filename, filename);
		}
		for (int i = 0; i < 100; ++i) {     //set all m_products to nullpointer
			m_products[i] = nullptr;
		}
		m_noOfProducts = 0;  //number of products is set to zero

		loadProductRecords();    //load the records from the file
	}
	AmaApp::~AmaApp() {

		for (int i = 0; i < m_noOfProducts; ++i) {
			m_products[i] = nullptr;
			delete[] m_products[i];   //deallocates all dynamic instances stored in the m_products array
		
		}
	}

	int AmaApp::run() 
{
		bool found = false;  //initialize all variables before case
		int i, j;
		int exit = 1;
		while (exit != 0)  //while the user does not input 0 keep running the program/call menu function
		{
			int selection = menu();
			switch (selection)    //using case for the user selection
			{
			case 0:   //user inputs 0 exit the program
				cout << "Goodbye!" << endl;
				exit = 0;
				break;
			case 1:
				listProducts();  //user inputs 1 then list the products by calling the listProducts() function				
				pause();
				break;
			case 2:  //user inputs 2 then list then serch for product and display it 
				char sku[max_length_sku];
				cout << "Please enter the product SKU: ";
				cin >> sku;
				j = 0;
				for (i = 0; i < m_noOfProducts; ++i) {
					if (*m_products[i] == sku) {
						if (j == 0) {
							cout << endl; //so it only prints 1 initial line when sku is found even though we are in a for loop
							j++;
						}
						m_products[i]->write(cout, write_human);  //displays the product found
						found = true;
					}
				}
				if (i == m_noOfProducts) { //only print out next line after all the lines have been printed to the screen
					cout << endl;
				}
				if (found == false) {  //if the product is not found, no matching sku
					cout << "No such product!" << endl;
				}
				pause();
				break;
			case 3:  //if user inputs 3 then add a non-perishable product by calling addProduct() function with N parameter
				addProduct('N');
				cout << endl;
				break;
			case 4:
				addProduct('P');  //if user inputs 4 then add a perishable product by calling addProduct() function with P parameter
				cout << endl;
				break;
			case 5:  // if user inputs 5 then search for product by sku and if found add quantity
				char s[max_length_sku];
				cout << "Please enter the product SKU: ";
				cin >> s;
				cout << endl;
				if (find(s) == nullptr) {
					cout << "No such product!" << endl << endl;
				}
				else {
					addQty(find(s));
					saveProductRecords();
				}
				break;
			case 6:  //if user inputs 6 then search for product by sku and delete
				char sb[max_length_sku];
				cout << "Please enter the product SKU: ";
				cin >> sb;
				cout << endl;
				if (nullptr != find(sb)) {
					deleteProductRecord(find(sb));
					cout << "Deleted!" << endl;
					loadProductRecords();
				}
				else {
					
					cout << "No such product!" << endl;
				}
				break;
			case 7:  //if user inputs 7 then sort the file and save it
				sict::sort(m_products, m_noOfProducts);
				saveProductRecords();
				cout << "Sorted!" << endl << endl;
				break;
			default:  // if user does not enter a number between 0 and 7 then print invalid input message
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
				break;
			}
		}
			return exit;  //returns 0
		
	}
		void AmaApp::pause() const {
			
			cout << "Press Enter to continue...";
			cin.ignore();  //ignore charachter
			while (cin.get() != '\n');
			cout << endl;
		}

		int AmaApp::menu() const {
			int selection = -1;
			int check = -1;
			cout << "Disaster Aid Supply Management Program" << endl;
			cout << "--------------------------------------" << endl;
			cout << "1- List products" << endl;
			cout << "2- Search product" << endl;
			cout << "3- Add non-perishable product" << endl;
			cout << "4- Add perishable product" << endl;
			cout << "5- Add to product quantity" << endl;
			cout << "6- Delete product" << endl;
			cout << "7- Sort products" << endl;
			cout << "0- Exit program" << endl;
			cout << "> ";
			cin >> check;

			if (check >= 0 && check <= 7) {  //checks that user input is between or including 0-7, if not returns selection = -1;
				selection = check;
			}
			
			cin.clear();  //clear standard input buffer
			return selection;
		}

		void AmaApp::loadProductRecords()  //load products
		{

			if (m_products != nullptr) {  //delete all products from the array if != nullptr(if it has)
				for (int i = 0; i < 100; ++i) {
					m_products[i] = nullptr;
					delete[] m_products[i];
				}
			}                        //delete all products from the array (if any)
			int i = 0;             //set reading index to zero
			fstream file;                   //make an object of type fstream
			file.open(m_filename, ios::in);  //open the file for reading
			if (file.is_open()) {              //if file is open
				while (!file.fail()) {          //until reading fails
					char ch = 'x';
					file >> ch;
					if (createInstance(ch) != nullptr) {
						m_products[i] = createInstance(ch);
						file.ignore(1,',');
						m_products[i]->read(file, false);
						++i;
					}
				}
				m_noOfProducts = i;
			}
			
			file.close();
		}

		void AmaApp::saveProductRecords() const {

			fstream file;                   //make an object of type fstream
			file.open(m_filename, ios::out);  //open the file for writing

			for (int i = 0; i < m_noOfProducts; ++i) {
				m_products[i]->write(file, write_condensed);
				file << endl;
			}
			
			file.close();  //close file
		}

		void AmaApp::listProducts() const
		{
			//print heading
			cout << "------------------------------------------------------------------------------------------------" << endl;
			cout << "| ";
			cout << "Row";
			cout << " | ";
			cout.width(max_length_sku);
			cout.setf(ios::right);
			cout << "SKU";
			cout.unsetf(ios::right);
			cout <<" | ";
			cout.width(17);
			cout.setf(ios::left);
			cout << "Product Name";
			cout << "| ";
			cout.width(10);
			cout << "Unit";
			cout << " | ";
			cout.width(7);
			cout.setf(ios::right);
			cout.precision(2);
			cout.setf(ios::fixed);
			cout << "Price";
			cout << " |";
			cout.width(4);
			cout << "Tax";
			cout << " |";
			cout.width(7);
			cout << "QtyA";
			cout << " | ";
			cout.width(6);
			cout << "QtyN";
			cout << " | ";
			cout.width(10);
			cout.unsetf(ios::right);
			cout.setf(ios::left);
			cout << "Expiry";
			cout << " |" << endl;
			cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
			
			double totalCost = 0;
			for (int i = 1; i <= m_noOfProducts; ++i) {
				cout << "|";
				cout.width(4);
				cout.setf(ios::right);
				cout << i;
				cout << " |";
				cout.unsetf(ios::right);
				m_products[i-1]->write(cout, write_table);
				totalCost += m_products[i-1]->total_cost();              //because it needs the current object
				cout << endl;
			}
			cout << "------------------------------------------------------------------------------------------------" << endl;
			cout << "|";
			cout.width(81);
			cout.setf(ios::right);
			cout << "Total cost of support ($): ";
			cout << "| ";
			cout.precision(2);
			cout.setf(ios::fixed);
			cout.width(10);
			cout << totalCost << " |" << endl;
			cout.unsetf(ios::right);
			cout << "------------------------------------------------------------------------------------------------" << endl << endl;

		}
		void AmaApp::deleteProductRecord(iProduct* product) {

			fstream file;
			file.open(m_filename, ios::out);
			for (int i = 0; i < m_noOfProducts; ++i) { //writes to the file everything except if it matches the parameter
				if (m_products[i] != product) {
					m_products[i]->write(file, write_condensed);
					file << endl;
				}
			}
			file.close();
		}
		void AmaApp::sort(iProduct* products) {

			sict::sort(m_products, m_noOfProducts);

		}

		iProduct* AmaApp::find(const char* sku) const {

			for (int i = 0; i < m_noOfProducts; ++i) {
				if (*m_products[i] == sku) {  //if found return the product
					return m_products[i];
				}
			}
			return nullptr;  //else return nullptr if not found
		}
		void AmaApp::addQty(iProduct* product) {
			
			int num;
			product->write(cout, write_human);
			cout << endl << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> num;
			if (num > 0) {
				int needed = (product->qtyNeeded() - product->qtyAvailable());
				if (num > needed) {
					cin.clear();
					cout << "Too many items; only " << needed << " is needed. Please return the extra " << num - needed << " items."<< endl;
					*product += needed;
				}
				else
					*product += num;
				cout << endl << "Updated!" << endl;
			}
			else
				cout << "Invalid quantity value!" << endl;
				cin.clear();         //*after a fail have to call both clear AND ignore to handle the error  //clears error
				cin.ignore(1000, '\n');
				cout << endl;
			
			
		}
		void AmaApp::addProduct(char tag) {

			if (createInstance(tag) != nullptr) {

				m_products[m_noOfProducts] = createInstance(tag);
				m_products[m_noOfProducts]->read(cin, true);

				if (cin.fail()) {
					cout << *m_products[m_noOfProducts] << endl; //prints error message*
					cin.clear();         //*after a fail have to call both clear AND ignore to handle the error  //clears error
					cin.ignore(1000, '\n');   //deals with the bad characters
				}

				else {
					m_noOfProducts++;
					saveProductRecords();
					cout << endl << "Success!" << endl;
				}
			
			}
			
		}
}