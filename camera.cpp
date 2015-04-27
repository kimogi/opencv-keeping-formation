#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ctime>
#include <iostream>
#include <string>

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

int main(int argc, char* argv[]) {
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
		//cout << "New frame written to " << name << endl;
		
		long start = (long)time(NULL);
		Mat imgRedOnly;
		inRange(imgRotated, Scalar(0, 0, 100), Scalar(50, 50, 255), imgRedOnly);
		cout << "red frame time : " << (long)time(NULL)  << " " << start << endl;		

		imwrite(path + "red_image" + ".jpg", imgRedOnly);

		start = (long)time(NULL);
		Mat imgBounded = imgRotated.clone();
		double obj_width = bound(imgRedOnly, imgBounded);
		cout << "bound time : " << (long)time(NULL) << " " << start << endl;

		double obj_width_px = (2592/640)*obj_width;
		cout << "width : " << obj_width_px << " pixels" << endl;		
		double width_mm = 1.4 * obj_width_px/1000;
		cout << "width : " << width_mm << " mm" << endl;
		double real_width = 75;
		cout << "real width : " << real_width << " mm" << endl;
		double focal_len_mm = 3.6;
		cout << "focal length : " << focal_len_mm << " mm" << endl;
		double distance = (real_width/width_mm)	* focal_len_mm;
		cout << "distance : " << distance << " mm" << endl;	

		imwrite(path + "bounded_image" + ".jpg", imgBounded);
//	}
	return 0;
}
