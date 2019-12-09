#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

VideoCapture cap("video.mp4");
Mat frame, frame_HSV, frame_threshold;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int max_value_H = 360;
const int max_value = 255;
const int max_valueX = 1200;//1280 × 720
const int max_valueY = 700;
const String video_dorogi = "Video dorogi";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 220;
int high_H = max_value_H, high_S = max_value, high_V = max_value;

void transform(Point2f* frame_vertices, Point2f* frameCropped_vertices, Mat& frame, Mat& frameCropped)
{
	Mat M = getPerspectiveTransform(frame_vertices, frameCropped_vertices);
	warpPerspective(frame, frameCropped, M, frameCropped.size(), INTER_LINEAR, BORDER_CONSTANT);
}
static void on_low_H_thresh_trackbar(int, void*)
{
	low_H = min(high_H - 1, low_H);
	setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void*)
{
	high_H = max(high_H, low_H + 1);
	setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void*)
{
	low_S = min(high_S - 1, low_S);
	setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void*)
{
	high_S = max(high_S, low_S + 1);
	setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void*)
{
	low_V = min(high_V - 1, low_V);
	setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void*)
{
	high_V = max(high_V, low_V + 1);
	setTrackbarPos("High V", window_detection_name, high_V);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int low_X1 = 0, low_Y1 = 0, low_X2 = 0, low_Y2 = 0, low_X3 = 0, low_Y3 = 0, low_X4 = 0, low_Y4 = 0;
int high_X1 = 500, high_Y1 = 495, high_X2 = 800, high_Y2 = 495, high_X3 = 1120, high_Y3 = 650, high_X4 = 200, high_Y4 = 650;
static void X1_thresh_trackbar(int, void*)
{
	high_X1 = max(high_X1, low_X1 );
	setTrackbarPos("high_X1", video_dorogi, high_X1);
}
static void Y1_thresh_trackbar(int, void*)
{
	high_Y1 = max(high_Y1, low_Y1);
	setTrackbarPos("high_Y1", video_dorogi, high_Y1);
}
static void X2_thresh_trackbar(int, void*)
{
	high_X2 = max(high_X2, low_X2);
	setTrackbarPos("high_X2", video_dorogi, high_X2);
}
static void Y2_thresh_trackbar(int, void*)
{
	high_Y2 = max(high_Y2, low_Y2);
	setTrackbarPos("high_Y2", video_dorogi, high_Y2);
}
static void X3_thresh_trackbar(int, void*)
{
	high_X3 = max(high_X3, low_X3);
	setTrackbarPos("high_X3", video_dorogi, high_X3);
}
static void Y3_thresh_trackbar(int, void*)
{
	high_Y3 = max(high_Y3, low_Y3);
	setTrackbarPos("high_Y3", video_dorogi, high_Y3);
}
static void X4_thresh_trackbar(int, void*)
{
	high_X4 = max(high_X4, low_X4);
	setTrackbarPos("high_X4", video_dorogi, high_X4);
}
static void Y4_thresh_trackbar(int, void*)
{
	high_Y4 = max(high_Y4, low_Y4);
	setTrackbarPos("high_Y4", video_dorogi, high_Y4);
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) 
{


	while (1) {
		
		
		cap >> frame;

	if (frame.empty())
	{
		cout << "Could not open or find the video!\n" << endl;
		return -1;
	}
	
	Point2f frame_vertices[4];
	frame_vertices[0] = Point(high_X1, high_Y1);
	frame_vertices[1] = Point(high_X2, high_Y2);
	frame_vertices[2] = Point(high_X3, high_Y3);
	frame_vertices[3] = Point(high_X4, high_Y4);

	Point2f frameCropped_vertices[4];
	frameCropped_vertices[0] = Point(0, 0); 
	frameCropped_vertices[1] = Point(640, 0);
	frameCropped_vertices[2] = Point(640, 480);
	frameCropped_vertices[3] = Point(0, 480);

	Mat M = getPerspectiveTransform(frame_vertices, frameCropped_vertices);
	Mat frameCropped(480, 640, CV_8UC3);
	warpPerspective(frame, frameCropped, M, frameCropped.size(), INTER_LINEAR, BORDER_CONSTANT);

	Mat frame2Cropped(480, 640, CV_8UC3);
	transform(frame_vertices, frameCropped_vertices, frame, frame2Cropped);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
	createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
	createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
	createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
	createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
	createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
	cvtColor(frame2Cropped, frame_HSV, COLOR_BGR2HSV);
	inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namedWindow(video_dorogi, CV_WINDOW_AUTOSIZE);
	
	createTrackbar("high_X1", video_dorogi, &high_X1, max_valueX, X1_thresh_trackbar);
	createTrackbar("high_Y1", video_dorogi, &high_Y1, max_valueY, Y1_thresh_trackbar);
	createTrackbar("high_X2", video_dorogi, &high_X2, max_valueX, X2_thresh_trackbar);
	createTrackbar("high_Y2", video_dorogi, &high_Y2, max_valueY, Y2_thresh_trackbar);
	createTrackbar("high_X3", video_dorogi, &high_X3, max_valueX, X3_thresh_trackbar);
	createTrackbar("high_Y3", video_dorogi, &high_Y3, max_valueY, Y3_thresh_trackbar);
	createTrackbar("high_X4", video_dorogi, &high_X4, max_valueX, X4_thresh_trackbar);
	createTrackbar("high_Y4", video_dorogi, &high_Y4, max_valueY, Y4_thresh_trackbar);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	line(frame, Point(high_X1, high_Y1), Point(high_X2, high_Y2), Scalar(0, 255, 0), 2, LINE_AA);
	line(frame, Point(high_X2, high_Y2), Point(high_X3, high_Y3), Scalar(0, 255, 0), 2, LINE_AA);
	line(frame, Point(high_X3, high_Y3), Point(high_X4, high_Y4), Scalar(0, 255, 0), 2, LINE_AA);
	line(frame, Point(high_X4, high_Y4), Point(high_X1, high_Y1), Scalar(0, 255, 0), 2, LINE_AA);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//namedWindow(window_detection_name, CV_WINDOW_AUTOSIZE);
	imshow("video_dorogi", frame);
	//imshow("video only dorogi affin", frame_HSV);
	imshow(window_detection_name, frame_threshold);
	
	char key = (char)waitKey(30);
	if (key == 'q' || key == 27)
	{
		break;
	}
	}

	cap.release();
	destroyAllWindows();

	return 0;
}