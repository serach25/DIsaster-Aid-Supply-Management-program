//Name: Serach Boes
//Date of completion: April 6, 2019

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Date.h"
#include "Product.h"  //interface is iProduct.h 

namespace ama {

	class Perishable : public Product {  //will publicly inherit from Product
		Date m_expiry;
	public:
		Perishable(char type = 'P');
		std::ostream& write(std::ostream& out, int writeMode) const;
		std::istream& read(std::istream& in, bool interactive);
	};
}
#endif


