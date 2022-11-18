//Name: Serach (Sarah) Boes
//Date of completion: April 6, 2019


#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>  //include for ostream

namespace ama {
	class ErrorState
	{
		char* m_address;   //stores the address of the error message

	public:
		explicit ErrorState(const char* errorMessage = nullptr);   //constructer
		ErrorState(const ErrorState& other) = delete;  // prohibits copying of any ErrorState object
		ErrorState& operator=(const ErrorState& other) = delete;  // prohibits copy assignment
		~ErrorState();  // destructer
		operator bool() const;  // returns true if current instance is storing a valid message 
		ErrorState& operator=(const char* pText);  //overload of assignment operator
		void message(const char* pText);
		const char* message() const;
		friend std::ostream& operator<<(std::ostream& os, const ErrorState& message);
	};

}
#endif

