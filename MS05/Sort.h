//Name: Serach (Sarah) Boes
//Date of completion: April 6, 2019

#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict {

	template <typename T>
	void sort(T arr[], int size) {
		int i, j;
		T temp;
		for (i = size - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {
				if (*arr[j] > *arr[j + 1]) {
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
}
#endif