//Name: Serach Boes
//Date of completion: April 6, 2019

#include "Utilities.h"

namespace ama {

	double& operator+=(double& total, const iProduct& prod) {

		total += prod.total_cost();
		return total;
	}

	std::ostream& operator<<(std::ostream& out, const iProduct& prod) {

		return prod.write(out, write_human);

	}

	std::istream& operator>>(std::istream& in, iProduct& prod) {

		return prod.read(in, true);

	}

	iProduct* createInstance(char tag) {  //dynamically creates instances in the product hierarchy

		Product* product = nullptr;  //if product has any other value returns null

		if (tag == 'N' || tag == 'n') {
			product = new Product();   //don't pass tag because we want the capital N default value to always print
		}

		if (tag == 'P' || tag == 'p') {
			product = new Perishable();
		}

		return product;

	}
}