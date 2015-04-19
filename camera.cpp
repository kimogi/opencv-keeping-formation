#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened()) {
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

//	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

//   while (1)
//  {
	Mat frame;

	bool bSuccess = cap.read(frame); // read a new frame from video

	if (!bSuccess) {
		cout << "Cannot read a frame from video stream" << endl;
	//      break;
	}

	Mat mat_rotation = getRotationMatrix2D(Point(frame.rows/2, frame.cols/2), 180, 1);

	Mat rotated_frame;
	warpAffine(frame, rotated_frame, mat_rotation, frame.size());	

	imwrite( "image.jpg", rotated_frame);	
// }
	return 0;
}
