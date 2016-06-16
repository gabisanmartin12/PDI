/**
 * EJERCICIO 4:
 * 
 *     1 - Cargue la imagen rosas.jpg. Obtener una imagen binaria con las rosas
 *         segmentadas.
 *     2 - Descarte las regiones erroneas con el metodo apropiado.
 *     3 - Identifique las regiones con el metodo de etiquetado de componentes 
 *         conectadas (Probar hacerlo con crecimiento de regiones y ver si se
 *         puede hacer lo mismo).
 *     4 - Cuente automáticamente la cantidad de rosas presente en la imagen
 *         original, Dibuje un circulo de tamaño arbitrario en el centro de cada
 *         rosa.
 */
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../Funciones/functions.cpp"
#include <cmath>

using namespace cv;
using namespace std;
using namespace mypdi;

int main(int argc, char** argv) {
	Mat image, imageHsv, roses;
	
	// Read image
	image = imread("../Imagenes/rosas.jpg", CV_LOAD_IMAGE_COLOR);
	
	// Change to HSV color pallete
	cvtColor(image, imageHsv, CV_RGB2HSV);
	
	// Values for thresholding
	int minH = 117, maxH = 135,
		minS =  89, maxS = 255,
		minV = 113, maxV = 255;
	
	// Get the values for thresholding the image on HSV color pallete
	//getThresholdValuesForHsv(image, minH, maxH, minS, maxS, minV, maxV);
	
	// Thresholding the image
	inRange(
		imageHsv                 ,
		Scalar(minH, minS, minV) ,
		Scalar(maxH, maxS, maxV) ,
		roses
	);
	
	// Clonsing and Erode
	Mat EE = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(roses, roses, MORPH_CLOSE, EE);
	erode(roses, roses, EE);
	
	// Find contourns
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(roses, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	int index, rosesCounter = contours.size();
	for (index = 0; index < rosesCounter; index++) {
		// Connected components
		Scalar color(rand()&255, rand()&255, rand()&255);
		drawContours(roses, contours, index, color, CV_FILLED);
		
		// Draw circles enclosing the roses
		Point2f center;
		float radius;
		minEnclosingCircle(contours[index], center, radius);
		circle(roses, center, (int)radius+5, color);
	}
	
	// Print number of roses
	cout << "En la imagen hay " << rosesCounter << " rosas." << endl;
	
	// Show image
	namedWindow("Image", CV_WINDOW_KEEPRATIO);
	imshow("Image", image);
	
	// Show roses
	namedWindow("Roses", CV_WINDOW_KEEPRATIO);
	imshow("Roses", roses);
	
	waitKey();
	
	return 0;
} 


