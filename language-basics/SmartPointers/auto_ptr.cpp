// C++ program to illustrate the use of auto_ptr 

// notice that auto_ptr has been replaced by unique_ptr in c++ 17 

#include <iostream> 
#include <memory> 

using namespace std; 

// creating class with overloaded constructor and destructor 
class Integer { 
public: 
	Integer() { cout << "Object Created" << endl; } 

	~Integer() { cout << "Object Destroyed" << endl; } 
}; 

// driver code 
int main() 
{ 
	// creating auto pointer to Integar class 
	auto_ptr<Integer> ptr(new Integer()); 

	// not using delete 

	return 0; 
}
