/*
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <stdlib.h>
#include <stdio.h>


using namespace cv;
using namespace std;



int main()
{
 Mat src1;
 src1 = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
 namedWindow("Original image", CV_WINDOW_AUTOSIZE);
 imshow("Original image", src1);

Mat gray, edge, draw;
 cvtColor(src1, gray, CV_BGR2GRAY);

Canny(gray, edge, 50, 150, 3);

edge.convertTo(draw, CV_8U);
 namedWindow("imageCanny", CV_WINDOW_AUTOSIZE);
 imshow("imageCanny", draw);

 dst = cvCvtColor("imageHSV", COLOR_BGR2HSV);
	 imshow("imageHSV", draw);

 
waitKey(0);
 return 0;
}
*/
/*
//#include <cv.h>
//#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

// ��� �������� ������� RGB
IplImage* rgb = 0;
IplImage* r_plane = 0;
IplImage* g_plane = 0;
IplImage* b_plane = 0;
// ��� �������� ������� RGB ����� ��������������
IplImage* r_range = 0;
IplImage* g_range = 0;
IplImage* b_range = 0;
// ��� �������� ��������� ��������
IplImage* rgb_and = 0;

int Rmin = 0;
int Rmax = 256;

int Gmin = 0;
int Gmax = 256;

int Bmin = 0;
int Bmax = 256;

int RGBmax = 256;

//
// �������-����������� ��������
//
void myTrackbarRmin(int pos) {
	Rmin = pos;
	cvInRangeS(r_plane, cvScalar(Rmin), cvScalar(Rmax), r_range);
}

void myTrackbarRmax(int pos) {
	Rmax = pos;
	cvInRangeS(r_plane, cvScalar(Rmin), cvScalar(Rmax), r_range);
}

void myTrackbarGmin(int pos) {
	Gmin = pos;
	cvInRangeS(g_plane, cvScalar(Gmin), cvScalar(Gmax), g_range);
}

void myTrackbarGmax(int pos) {
	Gmax = pos;
	cvInRangeS(g_plane, cvScalar(Gmin), cvScalar(Gmax), g_range);
}

void myTrackbarBmin(int pos) {
	Bmin = pos;
	cvInRangeS(b_plane, cvScalar(Bmin), cvScalar(Bmax), b_range);
}

void myTrackbarBmax(int pos) {
	Bmax = pos;
	cvInRangeS(b_plane, cvScalar(Bmin), cvScalar(Bmax), b_range);
}

int main(int argc, char* argv[])
{
	// ��� �������� ������� ������ ����������
	char* filename = argc == 2 ? argv[1] : "Image0.jpg";
	// �������� ��������
	image = cvLoadImage(filename, 1);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// ������ ��������
	rgb = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	r_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	g_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	b_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	r_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	g_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	b_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	rgb_and = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	//  ��������
	cvCopy(image, rgb);
	// ��������� �� �������� ������
	cvSplit(rgb, b_plane, g_plane, r_plane, 0);

	//
	// ���������� ����������� � ������������ ��������
	// � ������� HSV
	double framemin = 0;
	double framemax = 0;

	cvMinMaxLoc(r_plane, &framemin, &framemax);
	printf("[R] %f x %f\n", framemin, framemax);
	Rmin = framemin;
	Rmax = framemax;
	cvMinMaxLoc(g_plane, &framemin, &framemax);
	printf("[G] %f x %f\n", framemin, framemax);
	Gmin = framemin;
	Gmax = framemax;
	cvMinMaxLoc(b_plane, &framemin, &framemax);
	printf("[B] %f x %f\n", framemin, framemax);
	Bmin = framemin;
	Bmax = framemax;

	// ���� ��� ����������� ��������
	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("R", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("G", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("B", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("R range", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("G range", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("B range", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("rgb and", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("Rmin", "R range", &Rmin, RGBmax, myTrackbarRmin);
	cvCreateTrackbar("Rmax", "R range", &Rmax, RGBmax, myTrackbarRmax);
	cvCreateTrackbar("Gmin", "G range", &Gmin, RGBmax, myTrackbarGmin);
	cvCreateTrackbar("Gmax", "G range", &Gmax, RGBmax, myTrackbarGmax);
	cvCreateTrackbar("Bmin", "B range", &Gmin, RGBmax, myTrackbarBmin);
	cvCreateTrackbar("Bmax", "B range", &Gmax, RGBmax, myTrackbarBmax);

	//
	// ��������� ���� �� �������� �����
	//
	if (image->width < 1920 / 4 && image->height < 1080 / 2) {
		cvMoveWindow("original", 0, 0);
		cvMoveWindow("R", image->width + 10, 0);
		cvMoveWindow("G", (image->width + 10) * 2, 0);
		cvMoveWindow("B", (image->width + 10) * 3, 0);
		cvMoveWindow("rgb and", 0, image->height + 30);
		cvMoveWindow("R range", image->width + 10, image->height + 30);
		cvMoveWindow("G range", (image->width + 10) * 2, image->height + 30);
		cvMoveWindow("B range", (image->width + 10) * 3, image->height + 30);
	}

	while (true) {

		// ���������� ��������
		cvShowImage("original", image);

		// ���������� ����
		cvShowImage("R", r_plane);
		cvShowImage("G", g_plane);
		cvShowImage("B", b_plane);

		// ���������� ��������� ���������� ��������������
		cvShowImage("R range", r_range);
		cvShowImage("G range", g_range);
		cvShowImage("B range", b_range);

		// ���������� 
		cvAnd(r_range, g_range, rgb_and);
		cvAnd(rgb_and, b_range, rgb_and);

		// ���������� ���������
		cvShowImage("rgb and", rgb_and);

		char c = cvWaitKey(33);
		if (c == 27) { // ���� ������ ESC - �������
			break;
		}
	}
	printf("\n[i] Results:\n");
	printf("[i][R] %d : %d\n", Rmin, Rmax);
	printf("[i][G] %d : %d\n", Gmin, Gmax);
	printf("[i][B] %d : %d\n", Bmin, Bmax);

	// ����������� �������
	cvReleaseImage(&image);
	cvReleaseImage(&rgb);
	cvReleaseImage(&r_plane);
	cvReleaseImage(&g_plane);
	cvReleaseImage(&b_plane);
	cvReleaseImage(&r_range);
	cvReleaseImage(&g_range);
	cvReleaseImage(&b_range);
	cvReleaseImage(&rgb_and);
	// ������� ����
	cvDestroyAllWindows();
	return 0;
}
*/


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