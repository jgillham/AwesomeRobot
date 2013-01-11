
#include <iostream>
class Returnable {
	int id;
  public:
	static int counter;
	Returnable(): id( counter++ ) {
		std::cout << "Returnable Constructor #" << id << std::endl;
	}
	~Returnable() {
		std::cout << "Returnable deconstructor #" << id << std::endl;
	}


};
int Returnable::counter = 0;
Returnable aFunction() {
	Returnable a;
	return a;
}
int main( int argc, char* args[] ) {
	std::cout << "Begin 1st test:" << std::endl;
	Returnable b = aFunction();
	std::cout << "End 1st test:" << std::endl;
	std::cout << "Begin 2st test:" << std::endl;
	aFunction();
	std::cout << "End 2st test:" << std::endl;

	return 0;
}
