#include<iostream>
#include <SerialStream.h>
//#define PORT = "/dev/ttyACM0"

using namespace std;
using namespace LibSerial;

void open(); 
void send(); 
SerialStream ardu;

int main()
{
	char data;
	while(data != 'q')
	{
		open();
		cin >> data;
		ardu << data;
	}
	return 0;
}

void open()
{
	ardu.Open("/dev/ttyACM0");
	ardu.SetBaudRate(SerialStreamBuf::BAUD_9600);
	ardu.SetCharSize(SerialStreamBuf::CHAR_SIZE_8); 
}
