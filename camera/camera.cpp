#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <wiringPi.h>

using namespace cv;
using namespace std;

double bound(Mat &image, Mat &canvas) {
	RNG rng(12345);
	vector<vector<Point> > contours;
 	vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	double max_width = 0;
	for(int i = 0; i < contours.size(); i++) { 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		if (boundRect[i].width > max_width) {
			max_width = boundRect[i].width;
		}
	}

	/// Draw polygonal contour + bonding rects + circles
	
	for( int i = 0; i< contours.size(); i++ ) {
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(canvas, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		rectangle(canvas, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
	}
	return max_width;
}

/*
wp         rp
0  GPIO_0  17 a1b
1  GPIO_1  18 a1a
2  GPIO_2  27 servo
3  GPIO_3  22 b1b
4  GPIO_4  23 b1a
5  GPIO_5  24
6  GPIO_6  25
7  GPIO_7  4
17 GPIO_8  28
18 GPIO_9  29
19 GPIO_10 30
20 GPIO_11 31
*/

#define LED_SWITCH 7

int main(int argc, char* argv[]) {
	
	wiringPiSetup();
  	pinMode(LED_SWITCH, OUTPUT);	
	
	int l=0;
	for (l=0; l<5; l++)
	{
		digitalWrite(LED_SWITCH, HIGH);
		cout << "led on\n" << endl;
		sleep(5);
		digitalWrite(LED_SWITCH, LOW);
		cout << "led off\n" << endl;
		sleep(5);
	}		
	
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened()) {
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

//	while (1) {
		Mat image;

		bool bSuccess = cap.read(image);

		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			//break;
			return 0;
		}

		Mat matRotation = getRotationMatrix2D(Point(dWidth/2, dHeight/2), 180, 1);

		Mat imgRotated;
		warpAffine(image, imgRotated, matRotation, image.size());	

		string path = "img/";
		imwrite(path + "org_image" + ".jpg", imgRotated);	

		Mat imgHSV;
                cvtColor(image, imgHSV, COLOR_BGR2HSV);

		Mat imgBlueOnly;	
		inRange(imgHSV, Scalar(180, 50, 50), Scalar(280, 255, 255), imgBlueOnly);

		//morphological opening (remove small objects from the foreground)
  		erode(imgBlueOnly, imgBlueOnly, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  		dilate(imgBlueOnly, imgBlueOnly, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   		//morphological closing (fill small holes in the foreground)
  		dilate(imgRedOnly, imgRedOnly, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  		erode(imgRedOnly, imgRedOnly, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );			

		imwrite(path + "blue_image" + ".jpg", imgBlueOnly);

		Mat imgBounded = imgRotated.clone();
		double obj_width = bound(imgBlueOnly, imgBounded);
		
		double obj_width_px = (2592/640)*obj_width;
		cout << "width : " << obj_width_px << " pixels" << endl;		
		double width_mm = 1.4 * obj_width_px/1000;
		cout << "width : " << width_mm << " mm" << endl;
		double real_width = 50;
		cout << "real width : " << real_width << " mm" << endl;
		double focal_len_mm = 3.6;
		cout << "focal length : " << focal_len_mm << " mm" << endl;
		double distance = (real_width/width_mm)	* focal_len_mm;
		cout << "distance : " << distance << " mm" << endl;	

		imwrite(path + "bounded_image" + ".jpg", imgBounded);
//	}
	return 0;
}
