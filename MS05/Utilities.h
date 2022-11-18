//Name: Serach (Sarah) Boes
//Date of completion: April 6, 2019

#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H
#include "Product.h"
#include "Perishable.h"

namespace ama {

	double& operator+=(double& total, const iProduct& prod);  //need to define this outside of the class because first parameter is not implicit, its a double
	std::ostream& operator<<(std::ostream& out, const iProduct& prod);
	std::istream& operator>>(std::istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}

#endif

