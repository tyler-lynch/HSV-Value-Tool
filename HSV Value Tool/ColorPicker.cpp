#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// HSV value variables.
Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

// Webcam feed varaibles.
VideoCapture cap(0);
Mat img;

int main() {

	// Builds Trackbars.
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {

		// Outputs the current HSV Values.
		cout << hmin << ", " << smin << ", " << vmin << ", " << hmax << ", " << smax << ", " << vmax << endl;

		// Displays and mirrors the webcam.
		cap.read(img);
		flip(img, img, 1);

		// Creates the image HSV Mat.
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		// Creates HSV Mask using trackbar values.
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		// Display the two video feeds.
		imshow("Image", img);
		imshow("Image Mask", mask);

		waitKey(1);
	}

	return 0;
}