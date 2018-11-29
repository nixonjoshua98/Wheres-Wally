#ifndef JN_BASE_IMAGE_H
#define JN_BASE_IMAGE_H

#include "JN_Matrix.h"

struct JN_Rect
{
	int x;
	int y;
	int w;
	int h;
};


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


	// Very useful virtual methods
	bool virtual CorrectWidth();
	bool virtual CorrectHeight();


	static bool Collide(int ax, int ay, int bx, int by, int w, int h);
	

	int GetImageWidth()  { return imgW; }	// Returns the image width...
	int GetImageHeight() { return imgH; }	// Returns the image height...

	// Image constants
	static const int REF_IMG_W = 36;
	static const int REF_IMG_H = 49;
	static const int LARGE_IMG_W = 1024;
	static const int LARGE_IMG_H = 768;

protected:
	int imgW;	// Width of image
	int imgH;	// Height of image

protected:
	JN_Matrix *img;	// Stores the image in a matrix
};

#endif // !JN_BASE_IMAGE_H
