#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>


using namespace std;
using namespace cv;

int main(int argc, const char** argv) {
	Mat src1;
	src1 = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original image", CV_WINDOW_AUTOSIZE);
	imshow("Original image", src1);

	Mat gray_image;
	cvtColor(src1, gray_image, CV_BGR2GRAY);

	Mat binary;
	threshold(gray_image, binary, 100, 255, CV_THRESH_BINARY);

	Mat tohsv;
	threshold(src1, tohsv, 150, 255, CV_BGR2HSV);

	Mat toBGR;
	threshold(src1, toBGR, 150, 255, CV_BGR2RGB);

	Mat gray, edge, draw;
	cvtColor(src1, gray, CV_BGR2GRAY);

	Canny(gray, edge, 50, 150, 3);
	edge.convertTo(draw, CV_8U);


	

	imshow("Original image", src1);
	imshow("gray image", gray_image);
	imshow("Binary", binary);
	imshow("HSV", tohsv);
	imshow("imageCanny", draw);
	imshow("RGB", toBGR);

	waitKey(0);
	return 0;
}