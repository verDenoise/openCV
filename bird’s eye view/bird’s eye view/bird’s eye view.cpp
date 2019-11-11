#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

int main() {

	VideoCapture cap("video.mp4");
	
	while (1) {
		
		Mat frame;
		cap >> frame;

	if (frame.empty())
	{
		cout << "Could not open or find the video!\n" << endl;
		return -1;
	}
	
	/* Попытка выбрать нужную область
	Rect r(230, 520, 600, 250);
	Mat frame2;
	frame(r).copyTo(frame2);
	*/
	//работает, но проблема с координатами
	/*Point2f frameTri[4];
	frameTri[0] = Point2f(0.f, 0.f);
	frameTri[1] = Point2f(frame.cols - 1.f, 0.f);
	frameTri[2] = Point2f(0.f, frame.rows - 1.f);
	frameTri[3] = Point2f(1.f, 1.f);
	Point2f dstTri[4];
	dstTri[0] = Point2f(0.f, frame.rows * 0.33f);
	dstTri[1] = Point2f(frame.cols * 0.85f, frame.rows * 0.25f);
	dstTri[2] = Point2f(frame.cols * 0.15f, frame.rows * 0.7f);
	dstTri[3] = Point2f(1.f, frame.rows * 1.f);
	Mat warp_mat = getAffineTransform(frameTri, dstTri);
	Mat warp_dst = Mat::zeros(frame.rows, frame.cols, frame.type());
	warpAffine(frame, warp_dst, warp_mat, warp_dst.size());
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	Mat rot_mat = getRotationMatrix2D(center, angle, scale);
	Mat warp_rotate_dst;
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());*/  






	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Output image is set to white
	Mat frameOut = Mat::ones(frame.size(), frame.type());
	frameOut = Scalar(1.0, 1.0, 1.0, 1.0);

	// Input 
	vector <Point2f> tri1;
	tri1.push_back(Point2f(300, 440));
	tri1.push_back(Point2f(1000, 440));
	tri1.push_back(Point2f(300, 660));
	tri1.push_back(Point2f(1000, 660));

	// Output 
	vector <Point2f> tri2;
	tri2.push_back(Point2f(500, 330));//1
	tri2.push_back(Point2f(800, 330));//2
	tri2.push_back(Point2f(500, 600));//4
	tri2.push_back(Point2f(800, 600));//3

	Rect r1 = boundingRect(tri1);
	Rect r2 = boundingRect(tri2);

	// Offset points by left top corner of the respective rectangles
	vector<Point2f> tri1Cropped, tri2Cropped;
	vector<Point> tri2CroppedInt;

	for (int i = 0; i < 3; i++)
	{
		tri1Cropped.push_back(Point2f(tri1[i].x - r1.x, tri1[i].y - r1.y));
		tri2Cropped.push_back(Point2f(tri2[i].x - r2.x, tri2[i].y - r2.y));

		// fillConvexPoly needs a vector of Point and not Point2f
		tri2CroppedInt.push_back(Point((int)(tri2[i].x - r2.x), (int)(tri2[i].y - r2.y)));
	}

	// Apply warpImage to small rectangular patches
	Mat frameCropped;
	frame(r1).copyTo(frameCropped);
	//find Affine transform
		Mat warpMat = getAffineTransform(tri1Cropped, tri2Cropped);
	// Apply the Affine Transform 
	Mat frame2Cropped = Mat::zeros(r2.height, r2.width, frameCropped.type());
	warpAffine(frameCropped, frame2Cropped, warpMat, frame2Cropped.size(), INTER_LINEAR, BORDER_REFLECT_101);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	imshow("video dorogi", frame);
	imshow("video only dorogi", frameCropped);
	imshow("video only dorogi affin", frame2Cropped);

	char c = (char)waitKey(25);
	if (c == 27)
		break;
	}

	cap.release();
	destroyAllWindows();

	return 0;
}