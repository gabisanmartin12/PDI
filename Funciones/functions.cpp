/**
 * FUNCTIONS
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

using namespace std;

/**Funciones auxiliares
 */
namespace mypdi{
	typedef unsigned char byte;

	/*************************************************************************/
	/******************************* METHODS *********************************/
	/*************************************************************************/
	
	/**
	 * Get addition of bit planes of an image
	 *
	 * @param {Mat} image Image to use
	 * @param {int} start Bit plane to start the addition
	 * @param {int} end   Bit plane to finish the addition
	 */
	cv::Mat addBitPlanes(cv::Mat image, int start, int end);

	/**
	 * Aplly average filter to an image
	 *
	 * @param {Mat} image Image to use
	 * @param {int} m     Number of mask rows
	 * @param {int} n     Number of mask cols
	 * @param {Mat} mask  Mask to use
	 */
	cv::Mat applyAveragingFilter(cv::Mat image, int m, int n, cv::Mat mask);

	/**
	 * Aplly gamma transformation to an image
	 *
	 * @param {Mat}   image Image to apply the transformation
	 * @param {float} c     Constant to multiply
	 */
	cv::Mat applyGammaTransformation(cv::Mat image, float gamma, float c=1, float e=0);

	/**
	 * Aplly log transformation to an image
	 *
	 * @param {Mat}   image Image to apply the transformation
	 * @param {float} c     Constant to multiply
	 */
	cv::Mat applyLogTransformation(cv::Mat image, float c=1);

	/**
	 * Aplly negative transformation to an image
	 *
	 * @param {Mat} image Image to apply the transformation
	 */
	cv::Mat applyNegativeTransformation(cv::Mat image);
	
	/**
	 * Binarize an image
	 *
	 * @param {Mat} image Image to binarize
	 */
	cv::Mat binarize(cv::Mat image);
	
	/**
	 * Build a structuring element determinated
	 *
	 * @param {int} row Number of rows for EE
	 * @param {int} col Number of columns for EE
	 */
	cv::Mat buildStructuringElement(int row, int col);
	
	/**
	 * Add m rows both top and bottom and add n cols both left and right with 0
	 *
	 * @param {Mat} image Image to use
	 * @param {int} m     Number of rows to add
	 * @param {int} n     Number of cols to add
	 */
	cv::Mat ceroPadding(cv::Mat image, int m, int n);
	
	/**
	 * Apply the correlation between an image and mask
	 *
	 * @param {Mat} image Image to use
	 * @param {Mat} mask  Mask to use
	 */	
	cv::Mat correlation(cv::Mat image, cv::Mat mask);

	/**
	 * Get a determinated bit plane of an image
	 *
	 * @param {Mat} image    Image to use
	 * @param {int} bitPlane Number of bit plane to return
	 */
	cv::Mat getBitPlane(cv::Mat image, int bitPlane);

	/**
	 * Calcule root mean squere between two images.
	 *
	 * @param {Mat} firstImage  First image to calcule rms
	 * @param {Mat} secondImage Second image to calcule rms
	 */
	double getECM(cv::Mat firstImage, cv::Mat secondImage);
	
	/**
	 * Get thresholds for filter in HSV color pallet
	 *
	 * @param {Mat} image  Image to use
	 * @param {int} minHue Minumum value of hue component
	 * @param {int} maxHue Maximum value of hue component
	 * @param {int} minSat Minimum value of saturation component
	 * @param {int} maxSat Maximum value of saturation component 
	 * @param {int} minVal Minimum value of intensity component
	 * @param {int} maxVal Maximum value of intensity component
	 */
	void getThresholdValuesForHsv(cv::Mat image, int &minHue, int &maxHue, int &minSat, int &maxSat, int &minVal, int &maxVal);
	
	/**
	 * Get thresholds for filter in RGB color pallet
	 *
	 * @param {Mat} image  Image to use
	 * @param {int} minR Minumum value of red component
	 * @param {int} maxR Maximum value of red component
	 * @param {int} minG Minimum value of green component
	 * @param {int} maxG Maximum value of green component 
	 * @param {int} minB Minimum value of blue component
	 * @param {int} maxB Maximum value of blue component
	 */
	void getThresholdValuesForRgb(cv::Mat image, int &minR, int &maxR, int &minG, int &maxG, int &minB, int &maxB);

	/**
	 * Add m rows both top and bottom and add n cols both left and right with
	 * mirror values
	 *
	 * @param {Mat} image Image to use
	 * @param {int} m     Number of rows of the mask
	 * @param {int} n     Number of cols of the mask
	 */
	cv::Mat mirror(cv::Mat image, int m, int n);

	/**
	 * Add m rows both top and bottom and add n cols both left and right
	 * repeating the first and las values respectively.
	 *
	 * @param {Mat} image Image to use
	 * @param {int} m     Number of rows of the mask
	 * @param {Mat} n     Number of cols of the mask
	 */
	cv::Mat repeat(cv::Mat image, int m, int n);
	
	/**
	* Print Mat values on console
	*
	* @param {Mat} mat Matrix to print its values.
	*/
	void printValues(cv::Mat mat);
	
	/**
	 * Get intensity profile from image
	 *
	 * @param {Mat} image Image to use
	 * @param {int}   row Row to scan
	 */
	vector<int> scanLine(cv::Mat image, int row);
	
	/*************************************************************************/
	/****************************** CALLBACKS ********************************/
	/*************************************************************************/
	
	/**
	 * OnMouseClickCallback on EE
	 *
	 * @param {int}   event Event
	 * @param {int}       x Column clicked
	 * @param {int}       y Row clicked
	 * @param {int}       ~ Don't care
	 * @param {void*} param Params to be used into callback
	 */
	void buildStructuringElementMouseCallback(int event, int x, int y, int, void* param);
	
}

namespace mypdi{
	
	/*************************************************************************/
	/******************************* METHODS *********************************/
	/*************************************************************************/

	/**
	 * Get addition of bit planes of an image
	 */
	 cv::Mat addBitPlanes(cv::Mat image, int start, int end) {
		// Get size of image
		int cols = image.cols;
		int rows = image.rows;

		// Inicialize image to work
		cv::Mat imageWork = cv::Mat::zeros(rows, cols, CV_8UC(1));

		// Calcule the addition of bit planes
		for (start; start <= end; start++) {
			cv::Mat plane = getBitPlane(image, start);
			imageWork += plane;
		}

		return imageWork;
	}

	/**
	 * Aplly average filter to an image
	 */
	cv::Mat applyAveragingFilter(cv::Mat image, int m, int n, cv::Mat mask) {
		if (mask.empty()) { mask = cv::Mat::ones(m, n, CV_8UC(1)); }

		// Apply 0-padding to image
		cv::Mat imageWork = mypdi::ceroPadding(image, m-1, n-1);

		// Calculate correlation
		imageWork = mypdi::correlation(imageWork, mask);

		// Define ROI (Region of interest)
		cv::Rect roi(n-1, m-1, image.cols, image.rows);

		// Crop image
		cv::Mat croppedImage = imageWork(roi);

		return croppedImage;
	}

	/**
	 * Aplly gamma transformation to an image
	 */
	cv::Mat applyGammaTransformation(cv::Mat image, float gamma, float c, float e) {
		cv::Mat outputImage;
		image.copyTo(outputImage);

		// Get limmits for loops
		int rows = image.rows;
		int cols = image.cols;

		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				// Get gray level from current pixel
				int grayLevel = image.at<uchar>(x,y);
				// Apply gamma transformation
				outputImage.at<uchar>(x,y) = c*pow(grayLevel+e, gamma);
			}
		}

		return outputImage;
	}

	/**
	 * Aplly log transformation to an image
	 */
	cv::Mat applyLogTransformation(cv::Mat image, float c) {
		cv::Mat outputImage;
		image.copyTo(outputImage);

		// Get limmits for loops
		int rows = image.rows;
		int cols = image.cols;

		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				// Get gray level from current pixel
				int grayLevel = image.at<uchar>(x,y);
				//int s = c*log(1+grayLevel);
				// Apply log transformation
				outputImage.at<uchar>(x,y) = c*log(1+grayLevel);
			}
		}

		cv::normalize(outputImage, outputImage, 0, 255);

		return outputImage;
	}

	/**
	 * Aplly negative transformation to an image
	 */
	inline cv::Mat applyNegativeTransformation(cv::Mat image) {
		cv::Mat outputImage;
		image.copyTo(outputImage);

		// Get limmits for loops
		int rows = image.rows;
		int cols = image.cols;

		// Get max and min values
		double min, max;
		cv::minMaxLoc(image, &min, &max);

		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				// Get gray level from current pixel
				int grayLevel = image.at<uchar>(x,y);
				// Apply negative transformation
				outputImage.at<uchar>(x,y) = max-grayLevel;
			}
		}

		return outputImage;
	}
	
	/**
	 * Binarize an image
	 */
	cv::Mat binarize(cv::Mat image, int &minIntensity, int &maxIntensity) {
		// Create image to work
		cv::Mat workImage;
		
		// Create window
		cv::namedWindow("Binarize image", CV_WINDOW_KEEPRATIO);
		// Show image
		imshow("Binarize image", image);
		
		// Create trackbars
		cv::createTrackbar("Min intensity", "Binarize image", &minIntensity, maxIntensity);
		cv::createTrackbar("Max intensity", "Binarize image", &maxIntensity, maxIntensity);
		
		do {
			// Threshold image with that values of each HSV component
			inRange(
				image                     ,
				cv::Scalar(minIntensity) ,
				cv::Scalar(maxIntensity) ,
				workImage
			);
			// Show image thresholded
			imshow("Binarize image", workImage);
		} while(cv::waitKey(33) != 27);
		
		// Delete all windows
		cv::destroyAllWindows();
		
		// Apply threshold
		cv::threshold(image, workImage, minIntensity, maxIntensity, CV_THRESH_BINARY_INV);
		
		return workImage;
	}
	
	/**
	 * Build a structuring element determinated
	 *
	 * @param {int} row Number of rows for EE
	 * @param {int} col Number of columns for EE
	 */
	cv::Mat buildStructuringElement(int row, int col) {
		cv::Mat EE = cv::Mat::zeros(row, col, CV_8UC(1));
		
		cv::namedWindow("Build structuring element", CV_WINDOW_KEEPRATIO);
		cv::imshow("Build structuring element", EE);
		setMouseCallback("Build structuring element", buildStructuringElementMouseCallback, &EE);
		cv::waitKey();
		
		cv::destroyWindow("Build structuring element");
		
		return EE;
	}

	/**
	 * Add m rows both top and bottom and add n cols both left and right with 0's
	 */
	cv::Mat ceroPadding(cv::Mat image, int m, int n) {
		// Get size of image
		int rows = image.rows;
		int cols = image.cols;

		// 0-padding
		cv::Mat imageWork = cv::Mat::zeros(rows+2*m, cols+2*n, CV_8UC(1));

		// Calculate loop limits
		int rowStart = m;
		int rowEnd   = rows+m;
		int colStart = n;
		int colEnd   = cols+n;

		// Center the image on imageWork
		for (int x=rowStart; x<rowEnd; x++) {
			for (int y=colStart; y<colEnd; y++) {
				imageWork.at<uchar>(x,y) = image.at<uchar>(x-m, y-n);
			}
		}

		return imageWork;
	}

	/**
	 * Apply the correlation between an image and mask
	 */
	cv::Mat correlation(cv::Mat image, cv::Mat mask) {
		// Get image size
		int imageRows = image.rows;
		int imageCols = image.cols;

		// Initialize image to work
		cv::Mat imageWork = cv::Mat::zeros(imageRows, imageCols, CV_8UC(1));

		// Get mask size
		int maskRows = mask.rows;
		int maskCols = mask.cols;

		// Calculate starts and ends of loops
		int startRow     = maskRows-1;
		int endRow       = imageRows-startRow;
		int startCol     = maskCols-1;
		int endCol       = imageCols-startCol;
		int startMaskRow = -(maskRows-1)/2;
		int endMaskRow   = -startMaskRow;
		int startMaskCol = -(maskCols-1)/2;
		int endMaskCol   = -startMaskCol;

		// Image loop
		for (int x=startRow; x<endRow; x++) {
			for (int y=startCol; y<endCol; y++) {
				// Initialize sum of products
				int sum = 0;
				// Mask loop
				for (int s=startMaskRow; s<=endMaskRow; s++){
					for (int t=startMaskCol; t<=endMaskCol; t++) {
						// Get mask value
						int maskValue   = mask.at<uchar>(s-startMaskRow,t-startMaskCol);
						// Get pixel value
						int pixelValue  = image.at<uchar>(x+s,y+t);
						// Add product
						sum            += maskValue*pixelValue;
					}
				}
				// Save new pixel value
				imageWork.at<uchar>(x, y) = sum/(maskRows*maskCols);
			}
		}

		return imageWork;
	}

	/**
	 * Get a determinated bit plane of an image
	 */
	cv::Mat getBitPlane(cv::Mat image, int bitPlane) {
		cv::Mat imageWork;
		image.copyTo(imageWork);

		// Get limmits for loops
		int rows = imageWork.rows;
		int cols = imageWork.cols;

		// Calculate pixel value of this plane
		int pot = pow(2, bitPlane);

		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				// If pixel value has component in this plane
				if (image.at<uchar>(x, y) & pot) {
					imageWork.at<uchar>(x, y) = pot;
				} else {
					imageWork.at<uchar>(x, y) = 0;
				}
			}
		}

		return imageWork;
	}

	/**
	 * Calcule root mean squere between two images.
	 */
	double getECM(cv::Mat firstImage, cv::Mat secondImage) {
		// Initialize root mean square
		double ecm = 0;

		// Get limmits for loops
		int rows = firstImage.rows;
		int cols = firstImage.cols;

		// Count of samples
		int N = rows*cols;

		// Calcule rms
		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				int r1  = firstImage.at<uchar>(x, y);
				int r2  = secondImage.at<uchar>(x, y);
				ecm    += pow(r2-r1, 2);
			}
		}

		ecm /= N;

		return ecm;
	}
	
	/**
	 * Get thresholds for filter in hsv color pallet
	 */
	void getThresholdValuesForHsv(cv::Mat image, int &minHue, int &maxHue, int &minSat, int &maxSat, int &minVal, int &maxVal) {
		// Initialize imageHsv image
		cv::Mat imageHsv, imageHsvThresholded;
		
		// Convert image to Hsv colors
		cv::cvtColor(image, imageHsv, CV_RGB2HSV);
		
		// Create windows to use
		namedWindow("Thresholds", CV_WINDOW_FREERATIO);
		namedWindow("Image"     , CV_WINDOW_KEEPRATIO);
		namedWindow("Image HSV" , CV_WINDOW_KEEPRATIO);
		
		// Show images
		imshow("Image", image);
		
		// Create trackbars
		createTrackbar("Hue min", "Thresholds", &minHue, maxHue);
		createTrackbar("Hue max", "Thresholds", &maxHue, maxHue);
		createTrackbar("Sat min", "Thresholds", &minSat, maxSat);
		createTrackbar("Sat max", "Thresholds", &maxSat, maxSat);
		createTrackbar("Val min", "Thresholds", &minVal, maxVal);
		createTrackbar("Val max", "Thresholds", &maxVal, maxVal);
		
		do {
			// Threshold image with that values of each HSV component
			inRange(
				imageHsv                       ,
				Scalar(minHue, minSat, minVal) ,
				Scalar(maxHue, maxSat, maxVal) ,
				imageHsvThresholded
			);
			// Show image thresholded
			imshow("Image HSV", imageHsvThresholded);
		} while(waitKey(33) != 27);
		
		// Delete all windows
		destroyAllWindows();
	}
	
	/**
	 * Get thresholds for filter in RGB color pallet
	 */
	void getThresholdValuesForRgb(cv::Mat image, int &minR, int &maxR, int &minG, int &maxG, int &minB, int &maxB) {
		// Initialize imageHsv image
		cv::Mat imageThresholded;
		
		// Create windows to use
		namedWindow("Thresholds", CV_WINDOW_FREERATIO);
		namedWindow("Image"     , CV_WINDOW_KEEPRATIO);
		
		// Show images
		imshow("Image", image);
		
		// Create trackbars
		createTrackbar("Red min"  , "Thresholds", &minR, maxR);
		createTrackbar("Red max"  , "Thresholds", &maxR, maxR);
		createTrackbar("Green min", "Thresholds", &minG, maxG);
		createTrackbar("Green max", "Thresholds", &maxG, maxG);
		createTrackbar("Blue min" , "Thresholds", &minB, maxB);
		createTrackbar("Blue max" , "Thresholds", &maxB, maxB);
		
		do {
			// Threshold image with that values of each HSV component
			inRange(
				image                     ,
				Scalar(minR, minG, minB) ,
				Scalar(maxR, maxG, maxB) ,
				imageThresholded
			);
			// Show image thresholded
			imshow("Image", imageThresholded);
		} while(waitKey(33) != 27);
		
		// Delete all windows
		destroyAllWindows();
	}

	/**
	 * Add m rows both top and bottom and add n cols both left and right with
	 * mirror the first and last row and col.
	 */
	cv::Mat mirror(cv::Mat image, int m, int n) {
		cv::Mat imageWork;

		// Get image size
		int cols = image.cols;
		int rows = image.rows;

		// Calculate loop limmits
		int rowStart = 0;
		int rowEnd   = rows+2*(m-1);
		int colStart = 0;
		int colEnd   = cols+2*(n-1);

		// Initialize new image
		imageWork = cv::Mat::zeros(rowEnd, colEnd, CV_8UC(1));

		for (int x=rowStart; x<rowEnd; x++) {
			int rowToAccess;

			// Calculate row to access
			if (x<m-1) { rowToAccess = m-1-x; }
			else if (x<rows+m-1) { rowToAccess = x-m+1; }
			else { rowToAccess = 2*(rows-1)-x+m-1; }

			for (int y=colStart; y<colEnd; y++) {
				int colToAccess;
				
				// Calculate col to access
				if (y<n-1) { colToAccess = n-1-y; }
				else if (y<cols+n-1) { colToAccess = y-n+1; }
				else { colToAccess = 2*(cols-1)-y+n-1; }

				// Get the new intensity value
				int grayLevel = image.at<uchar>(rowToAccess, colToAccess);
				imageWork.at<uchar>(x, y) = grayLevel;
			}
		}

		return imageWork;
	}

	/**
	 * Add m rows both top and bottom and add n cols both left and right
	 * repeating the first and las values respectively.
	 */
	cv::Mat repeat(cv::Mat image, int m, int n) {
		cv::Mat imageWork;

		// Get image size
		int cols = image.cols;
		int rows = image.rows;

		// Calculate loop limmits
		int rowStart = 0;
		int rowEnd   = rows+2*(m-1);
		int colStart = 0;
		int colEnd   = cols+2*(n-1);

		// Initialize new image
		imageWork = cv::Mat::zeros(rowEnd, colEnd, CV_8UC(1));

		for (int x=rowStart; x<rowEnd; x++) {
			int rowToAccess;	

			// Calculate row to access
			if (x<m) { rowToAccess = 0; }
			else if (x<rows+m-1) { rowToAccess = x-m+1; }
			else { rowToAccess = rows-1; }

			for (int y=colStart; y<colEnd; y++) {
				int colToAccess;
				
				// Calculate col to access
				if (y<n) { colToAccess = 0; }
				else if (y<cols+n-1) { colToAccess = y-n+1; }
				else { colToAccess = cols-1; }

				// Get the new intensity value
				int grayLevel = image.at<uchar>(rowToAccess, colToAccess);
				imageWork.at<uchar>(x, y) = grayLevel;
			}
		}

		return imageWork;
	}
	
	/**
	 * Print Mat values on console
	 */
	void printValues(cv::Mat mat) {
		// Get mat size
		int cols = mat.cols;
		int rows = mat.rows;
		
		// Show values
		for (int x=0; x<rows; x++) {
			for (int y=0; y<cols; y++) {
				int val  = mat.at<uchar>(x, y);
				cout << val << " ";
			}
			cout << endl;
		}
	}
	
	/**
	 * Get intensity profile from image
	 */
	vector<int> scanLine(cv::Mat image, int row) {
		// Initialize variables
		int cols;
		vector<int> line;
		
		// Get count of columns
		cols = image.cols;
		
		// Get all values of that row
		for(int j=0;j<cols;j++) { 
			int val = image.at<uchar>(row, j);
			line.push_back(val);
		}
		
		return line;
	}
	
	/*************************************************************************/
	/****************************** CALLBACKS ********************************/
	/*************************************************************************/
	
	/**
	 * OnMouseClickCallback on EE
	 */
	void buildStructuringElementMouseCallback(int event, int x, int y, int, void* param){
		// Check if the left button is clicked
		if(event != CV_EVENT_LBUTTONUP) { return; }
		
		// Cast EE
		cv::Mat* EE = (cv::Mat*) param;
		int val = (*EE).at<uchar>(y, x);
		// Check if pixel value is 0
		if (val == 0) {
			// If it is, set it to 255
			(*EE).at<uchar>(y, x) = 255; 
		} else {
			// if it isn't, set it to 0
			(*EE).at<uchar>(y, x) = 0;
		}
		
		// Update EE
		imshow("Build structuring element", *EE);
	}
}

#endif /* FUNCTIONS_H */
