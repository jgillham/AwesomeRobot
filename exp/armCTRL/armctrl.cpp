#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cmath>
#include <SerialStream.h>

using namespace LibSerial;
using namespace std;
using namespace cv;

int RRR(double xn, double yn);
void open();

int canny_threshold = 50;
SerialStream ardu;
int main(int argc, char** argv)
{
	VideoCapture cap(0);
	
//	if( !cap.isOpened());
//	return -1;

	namedWindow( "test",1);

	Mat frame;
	while(1)
	{
		cap >> frame;
		if(frame.empty())
		break;

		imshow( "test", frame);
		if(waitKey(30) >= 0) break;
	}

  Mat  src_gray;

//	frame = imread("filename000.jpg");

  /// Convert it to gray
  cvtColor( frame, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, canny_threshold, 100, 0, 0 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
//		cout << circles[i][0] / 33 -5<< "," << circles[i][1] / 33; 
      // circle center
      circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", frame );

	cout << 5 - circles[0][0] / 33 << "," << circles[0][1] / 33 << "\n"; 
	RRR(5 - circles[0][0] / 33, circles[0][1] / 33);

  waitKey(0);
	return 0;
}

int RRR(double xn, double yn)
{
	   double x, y, z, r, s, D;
   double theta1, theta2, theta3;
   double a2 = 3.8, a3 = 5, d = 3.5;
// char inChar;

/*   cout << "x: ";
   cin >> x;
   cout << "y: ";
   cin >> y;
   cout << "z: ";
   cin >> z;*/
	
	x = xn;
	y = yn;
	z = 0.8;

   r = sqrt((x*x) + (y*y));
   s = z - d;
   theta1 = (atan2(y,x))*57.2957795;

   D = ((r*r) + (s*s) -(a2*a2) - (a3*a3))/(2*a2*a3);

   theta3 = atan2(-sqrt(1 - D*D),D);

   theta2 = atan2(s, r) -atan2(a3*sin(theta3), a2+a3*cos(theta3));

   open();
   ardu << (int)theta1 << "," << (int)(90 -theta2 * 57.2957795) << ","
      << (int)(-theta3 *57.2957795)<< "f";
   cout << (int)theta1 << "," << (int)(90 -theta2 * 57.2957795) << ","
      << (int)(-theta3 *57.2957795)<< "\n";
   return 0;

}

void open()
{
   ardu.Open("/dev/ttyACM0");
   ardu.SetBaudRate(SerialStreamBuf::BAUD_9600);
   ardu.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
}

