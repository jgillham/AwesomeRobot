/**
Appears to display the video to the window frame.
*/
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;
int canny_threshold = 50;
int main(int argc, char** argv)
{
	VideoCapture cap(1);
	
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
      // circle center
      circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", frame );

  waitKey(0);
	return 0;
}
