/**
Using the keyboard for input, sends angles down to arduino.
*/
#include<iostream>
#include<cmath>
#include <SerialStream.h>
//#define PORT = "/dev/ttyACM0"

using namespace std;
using namespace LibSerial;

void open(); 
void send(); 
SerialStream ardu;
 
int main()
{
	double x, y, z, r, s, D;
	double theta1, theta2, theta3;
	double a2 = 3.8, a3 = 4.5, d = 3.5;
//	char inChar;
	
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "z: ";
	cin >> z;

//	cout << x << "," << y << "," << z << "\n";

	r = sqrt((x*x) + (y*y));
	s = z - d;
	theta1 = (atan2(y,x))*57.2957795;

	D = ((r*r) + (s*s) -(a2*a2) - (a3*a3))/(2*a2*a3);
//	D = (x*x + y*y +((z-d)*(z-d)) - a2*a2 - a3*a3)/(2*a2*a3);

//	theta3 = atan2(D, + sqrt( 1 - (D*D) ));
	theta3 = atan2(-sqrt(1 - D*D),D);

//	theta2 =  (atan2( sqrt(x*x + y*y), (z - d)) - atan2(a2 + a3*cos(theta3),
//		 a3*sin(theta3)));
	theta2 = atan2(s, r) -atan2(a3*sin(theta3), a2+a3*cos(theta3));

	open();
	ardu << (int)theta1 << "," << (int)(90 -theta2 * 57.2957795) << "," 
		<< (int)(-theta3 *57.2957795)<< "f";
	cout << (int)theta1 << "," << (int)(90 -theta2 * 57.2957795) << "," 
		<< (int)(-theta3 *57.2957795)<< "f";
	return 0;
}

void open()
{
	ardu.Open("/dev/ttyACM0");
	ardu.SetBaudRate(SerialStreamBuf::BAUD_9600);
	ardu.SetCharSize(SerialStreamBuf::CHAR_SIZE_8); 
}
