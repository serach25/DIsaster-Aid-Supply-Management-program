//Name: Serach Boes
//Date of completion: April 6, 2019

#include "ErrorState.h"

namespace ama {

	ErrorState::ErrorState(const char* errorMessage) {

		*this = errorMessage;   // uses the overload of the assignment operater function ErrorState& ErrorState::operator=(const char* pText) so eliminates writing duplicate code

	}


	ErrorState::~ErrorState() {

		m_address = nullptr;  // makes m_address point to nullptr after deallocating the memory that it was pointing to.
		delete[] m_address;  // deallocates memory that has been dynamically allocated by the current object

	}

	ErrorState::operator bool() const {

		bool message = false;
		if (nullptr != m_address)  // returns true if the current instance is not in the empty state (whatever the constructer sets it to)
			message = true;

		return message;
	}

	ErrorState& ErrorState::operator=(const char* pText) {


		if (nullptr == pText) {   //puts object into safe empty state if the address is nullptr
			m_address = nullptr;
		}
		else if (pText[0] == '\0') { //puts object into safe empty state if the address points to an empty string
			m_address = nullptr;
		}
		else  // if the address points to a message then dynamically allocates memory for the message and copies the message into that memory
		{
			int size = 0;  // variable to check the size of the char array of the pText

			for (int i = 0; pText[i] != '\0'; ++i)  //loop to save the size of the pText array in variable size.
				size++;

			m_address = new char[size];  //allocates new dynamic memory to copy the errorMessage with the correct size.  So the function won't allocate more memory than is needed to store the string.

			for (int j = 0; j < size; ++j)  //  copies the pText array into the new allocated dynamic memory
				m_address[j] = pText[j];
			//m_address[size] = '\0';
			m_address[size] = '\0'; //*** need to null terminate m_address, std::cout.operator<<(char*) will try to find \0 as its terminating character. 
			//must finish with the char '\0'. That's the way functions that play with char arrays know when the string finish in memory. 
			//If you forget the '\0' character at the end of the array, cout prints all the chars in the array and then goes on printing any data in memory after the array. 
			//So it will print garbage after the string if there is no null terminator
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {

		*this = pText;  // uses the overload of the assignment operater function ErrorState& ErrorState::operator=(const char* pText) so eliminates writing duplicate code

	}

	const char* ErrorState::message() const {

		return m_address;  // returns the address of the message stored in the current object, m_address is a pointer so holds an address
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& message) {
		if (nullptr != message.m_address)   // if the object is not in a safe empty state then prints the text stored in the current ErrorState object to a stream, 
			os << message.m_address;
		return os;  // if the object is in a safe empty state it does not 
	}
}