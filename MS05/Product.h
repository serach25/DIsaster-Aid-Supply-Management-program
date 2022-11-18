//Name: Serach (Sarah) Boes
//Date of completion: April 6, 2019

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"  //interface is iProduct.h 

namespace ama {

	class Product : public iProduct {  //will publicly inherit from the interface iProduct
		const char m_type;  //cannot be initialuzed in curly brackets within a constructer because itsa constant has to have a value the moment it is created  : a(30)
		char m_sku[max_length_sku];  // ex:   foo::foo(int val) : a(val)   only way to initialize const and references
		char m_unit[max_length_unit];
		char* m_nameOfProduct;  //resource instance pointer
		int m_quantityOnHand;
		int m_quantityNeeded;
		double m_price;   //price of product before tax
		bool m_taxable;   // if product is taxable
		ErrorState m_errorstate;
	protected:
		void message(const char* pText);
		bool isClear() const;
	public:
		Product(char type = 'N');
		Product(const char* SKU, const char* productName, const char* productUnit, double productPrice = 0, int Needed = 0, int OnHand = 0, bool taxStatus = true);
		Product(const Product&); //copy constructer
		~Product();  //destructer
		Product& operator=(const Product&); //copy assignment operator
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;  //accepts as parameter an un-modifiable refernece to iProduct
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interactive);
		std::ostream& write(std::ostream& out, int writeMode) const;
		const char* name() const;
	};
}
#endif

