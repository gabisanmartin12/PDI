#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../Implementaciones/RobertsOperator.cpp"
#include "../Funciones/functions.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Initialize 
	cv::Mat image, gx, gy;
	
	// Read image
	image = imread("../Imagenes/estanbul.tif", CV_LOAD_IMAGE_GRAYSCALE);
	
	// Create roberts operator object
	RobertsOperator Robert;
	
	// Apply roberts operators
	//gx = Robert.applyGx(image);
	//gy = Robert.applyGy(image);
	
	gx = Robert.getGx();
	
	mypdi::printValues(gx);
	
	// Show x gradient
	namedWindow("X Gradient", CV_WINDOW_KEEPRATIO);
	imshow("X Gradient", gx);
	
	// Show x gradient
	namedWindow("Y Gradient", CV_WINDOW_KEEPRATIO);
	imshow("Y Gradient", gy);
	
	waitKey();
	return 0;
} 


