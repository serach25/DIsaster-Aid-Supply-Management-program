//Name: Serach Boes
//Date of completion: April 6, 2019

#ifndef AMAAPP_H
#define AMAAPP_H
#include "iProduct.h"
#include "Utilities.h"

namespace ama {
	
	class AmaApp {
		
		char m_filename[256];  // holds the name of the text file that is storing the product information
		iProduct* m_products[100];  //array of iProduct pointers
		int m_noOfProducts;  //number of products

		void pause() const;  
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		void deleteProductRecord(iProduct* product);
		void sort(iProduct* products);
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);
		AmaApp(const AmaApp& other) = delete;  // prohibits copying of any AmaApp object
		AmaApp& operator=(const AmaApp& other) = delete;  //prohibits copy assignment

	public:
		AmaApp(const char* filename);  //custom constructer
		~AmaApp();  // destructer
		int run();  //runs the program
	};
}
#endif