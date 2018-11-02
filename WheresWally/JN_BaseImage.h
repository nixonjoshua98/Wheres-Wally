#ifndef JN_BASE_IMAGE_H
#define JN_BASE_IMAGE_H

#include "JN_Matrix.h"

class JN_BaseImage
{
public:
	JN_BaseImage();								// Default constructor
	JN_BaseImage(int w, int h, double *data);	// Standard constructor, sets all atrributes
	~JN_BaseImage();							// Deconstructor

	void SetImage(int w, int h, double *data);		// Alt to passing at constructor 
	double* GetImage();								// Returns matrix container
	double GetIndex(int i);							// Return 1 pixel at index
	double GetIndex(int x, int y);					// Return 1 pixel at index

	int GetImageWidth()  { return imgW; }	// Returns the image width...
	int GetImageHeight() { return imgH; }	// Returns the image height...

	// Image constants
	static const int REF_IMG_W = 36;		// Wally imagae width
	static const int REF_IMG_H = 49;		// Wally image height
	static const int LARGE_IMG_W = 1024;	// Cluttered image width
	static const int LARGE_IMG_H = 768;		// Cluttered image height

protected:
	int imgW;	// Width of image
	int imgH;	// Height of image

protected:
	JN_Matrix *img;	// Stores the image in a matrix
};

#endif // !JN_BASE_IMAGE_H
