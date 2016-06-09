#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../Funciones/functions.cpp"

using namespace cv;

cv::Mat binarize(cv::Mat image);
void binarizeTrackBarCallback(int threshold, void *params);

/**
 * Build set for exercise
 */
cv::Mat buildSet();

int main(int argc, char** argv) {
	// Initialize variables
	cv::Mat EE, image, set, setEroded, setDilated;
	
	// Check if image is given
	if (argc == 2) {
		// Read image
		image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		// Binarize image
		set = binarize(image);
	} else {
		// Build set
		set = buildSet();
	}
	
	// Show original image
	namedWindow("Original", CV_WINDOW_KEEPRATIO);
	imshow("Original", set);
	
	do {
		// Build EE
		EE  = mypdi::buildStructuringElement(3, 3);
		
		// Compute erode and dilate
		erode(set, setEroded, EE);
		dilate(set, setDilated, EE);
		
		// Show image eroded
		namedWindow("Erode", CV_WINDOW_KEEPRATIO);
		imshow("Erode", setEroded);
		
		// Show image eroded
		namedWindow("Dilate", CV_WINDOW_KEEPRATIO);
		imshow("Dilate", setDilated);
		
		// Show EE
		namedWindow("Structuring Element", CV_WINDOW_KEEPRATIO);
		imshow("Structuring Element", EE);
		
		// Waiting for key press
		waitKey();
		
		// Destroy EE, erode and dilate windows.
		destroyWindow("Structuring Element");
		destroyWindow("Erode");
		destroyWindow("Dilate");
		
	} while(waitKey() != 27);

	return 0;
}

cv::Mat binarize(cv::Mat image) {
	// Create image to work
	cv::Mat workImage;
	
	// Initialize threshold
	int threshold = 0;
	
	// Create window
	namedWindow("Binarize image", CV_WINDOW_KEEPRATIO);
	
	// Show image
	imshow("Binarize image", image);
	
	// Add to it a trackbar
	createTrackbar(
		"Threshold"              ,
		"Binarize image"         ,
		&threshold               ,
		254                      ,
		binarizeTrackBarCallback ,
		&image
	);
	
	// First call
	binarizeTrackBarCallback(0, &image);
	
	// Waiting for key pressed
	waitKey();
	
	// Get threshold
	threshold = getTrackbarPos("Threshold", "Binarize image");
	
	// Destroy binary window
	destroyWindow("Binarize image");
	
	// Apply threshold
	cv::threshold(image, workImage, threshold, 254, CV_THRESH_BINARY_INV);
	
	return workImage;
}

void binarizeTrackBarCallback(int threshold, void *param) {
	// Initialize image to work
	cv::Mat workImage;
	
	// Cast param
	cv::Mat* image = (cv::Mat *) param;
	
	// Create image to work
	(*image).copyTo(workImage);

	// Apply thresholding
	cv::threshold(workImage, workImage, threshold, 254, CV_THRESH_BINARY);
	
	// Show image reconstructed
	imshow("Binarize image", workImage);
}

/**
 * Build set for exercise
 */
cv::Mat buildSet() {
	cv::Mat set = cv::Mat::zeros(12, 11, CV_8U);
	set.at<uchar>(1,1) = 255;
	set.at<uchar>(1,2) = 255;
	set.at<uchar>(1,3) = 255;
	set.at<uchar>(2,3) = 255;
	set.at<uchar>(3,3) = 255;
	set.at<uchar>(4,2) = 255;
	set.at<uchar>(4,3) = 255;
	set.at<uchar>(4,4) = 255;
	set.at<uchar>(7,7) = 255;
	set.at<uchar>(7,8) = 255;
	set.at<uchar>(7,9) = 255;
	set.at<uchar>(8,9) = 255;
	set.at<uchar>(9,6) = 255;
	set.at<uchar>(9,7) = 255;
	set.at<uchar>(9,8) = 255;
	set.at<uchar>(9,9) = 255;	
	set.at<uchar>(10,7) = 255;
	set.at<uchar>(10,8) = 255;
	set.at<uchar>(10,9) = 255;
	set.at<uchar>(6,1) = 255;
	set.at<uchar>(7,2) = 255;
	set.at<uchar>(8,3) = 255;
	set.at<uchar>(10,1) = 255;
	set.at<uchar>(2,8) = 255;
	set.at<uchar>(3,7) = 255;
	set.at<uchar>(3,8) = 255;
	set.at<uchar>(3,9) = 255;
	set.at<uchar>(4,7) = 255;
	set.at<uchar>(4,8) = 255;
	set.at<uchar>(4,9) = 255;
	return set;
}




