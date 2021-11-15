#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
using namespace cv;

void draw_rect(Mat& img, vector< Rect >& v_rect) {

	for (auto it : v_rect) {
		rectangle(img, it, CV_RGB(255, 0, 0), 5);
	}
}



int main(int, char)
{
	int TH1 = 30;
	int TH_WIDTH;
	int TH_HEIGHT;
	int TH_AREA;
	float detection_ratio = 0.1;
	float detection_area = 0.01;
	float alpha = 0.2;
	float beta = (1.0 - alpha);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));

	Mat frame, frame_binary;
	Mat old_frame, bg_frame_binary;
	Mat sub_frame;
	VideoCapture stream1("cctv.mp4");

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera 1";
	}

	namedWindow("frame", 0);
	namedWindow("sub_frame", 0);


	while (1)
	{

		if (!(stream1.read(frame))) //get one frame form video   
			break;


		if (old_frame.empty())
		{
			old_frame = frame.clone();
			cvtColor(old_frame, bg_frame_binary, COLOR_BGR2GRAY);
			TH_WIDTH = int(old_frame.cols * detection_ratio);
			TH_HEIGHT = int(old_frame.rows * detection_ratio);

			//TH_AREA = int((old_frame.cols * old_frame.rows) * detection_area);
			continue;
		}


		
		cvtColor(frame, frame_binary, COLOR_BGR2GRAY);
		addWeighted(frame_binary, alpha, bg_frame_binary, beta, 0.0, bg_frame_binary);

		
		absdiff(bg_frame_binary, frame_binary, sub_frame);
		threshold(sub_frame, sub_frame, TH1, 255, THRESH_BINARY);
		morphologyEx(sub_frame, sub_frame, MORPH_CLOSE, element);

		// find contour
		vector< vector< Point> > contours;
		vector< Vec4i> hierarchy;
		findContours(sub_frame.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		drawContours(frame, contours, -1, CV_RGB(0, 0, 255), 1, 8, hierarchy);
		
		//Blob labeling
		vector< Point > pt;
		vector< Rect > v_rect;
		for (auto it : contours) {

			Rect mr = boundingRect(Mat(it));
			//v_rect.push_back(mr);
			Point pt2(mr.x, mr.y);

			if (mr.width > TH_WIDTH || mr.height > TH_HEIGHT) {
				v_rect.push_back(mr);
				pt.push_back(pt2);
			}	
	/*		double area = contourArea(it, false);
			if (area > TH_AREA)
			{
				v_rect.push_back(mr);
			}*/
		}

		draw_rect(frame, v_rect);
		for (auto p : pt) {
			putText(frame, "motion detection", p, 1, 3, CV_RGB(0, 255, 0), 3, 8);
		}

		if (v_rect.size() > 0)
		{
			char str[255];
			struct tm now;
			time_t rawtime = time(0);
			localtime_s(&now, &rawtime);

			sprintf_s(str, "y%d_m%d_h%d_m%d_s%d.jpg",
				now.tm_year, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
			imwrite(str, frame);
		}


		imshow("frame", frame);
		resizeWindow("frame", 640, 480);
		imshow("sub_frame", sub_frame);
		resizeWindow("sub_frame", 640, 480);
	

		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}