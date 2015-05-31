#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ctime>
#include <sys/time.h>
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
	/*
	for( int i = 0; i< contours.size(); i++ ) {
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(canvas, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		rectangle(canvas, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
	} */
	return max_width;
}

long millisSinceEpoch()
{
	struct timeval tp;
    	gettimeofday(&tp, NULL);
    	long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;
	return mslong;
}

int main(int argc, char* argv[]) {
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	long long count = -1;	

	while (1) {
		long long timeStart = millisSinceEpoch();
		Mat image;
		
		bool bSuccess = cap.read(image);
		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			return 0;
		}
		count++;
		if (count % 11 != 0)
		{
			continue;
		}
	
		Mat imgHSV;
                cvtColor(image, imgHSV, COLOR_BGR2HSV);

		Mat imgBlueOnly;	
		inRange(imgHSV, Scalar(100, 50, 50), Scalar(140, 255, 255), imgBlueOnly);

		Mat imgBounded = image.clone();
		double obj_width = bound(imgBlueOnly, imgBounded);
		
		double obj_width_px = (2592/640)*obj_width;
		double width_mm = 1.4 * obj_width_px/1000;
		double real_width = 50;
		double focal_len_mm = 3.6;
		double distance = (real_width/width_mm)	* focal_len_mm;
		long long endTime = millisSinceEpoch() - timeStart;
		
		cout << "distance : " << distance << " mm" << endl;
		cout << "time : " << endTime << "ms" << endl;
	}
	cap.release();
	return 0;
}
