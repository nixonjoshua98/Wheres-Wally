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
	void Output2PGM(char *fileName, bool &flag);	// Output the image to PGM
	double GetIndex(int i);							// Return 1 pixel at index
	double GetIndex(int x, int y);					// Return 1 pixel at index

	static double* ReadTextFile(char *fileName, int w, int h, bool &flag);
	static void Output2PGM(char *fileName, int w, int h, double *_data, bool &flag);

	int imgW;	// Width of image
	int imgH;	// Height of image

protected:
	JN_Matrix *img;
};

#endif // !JN_BASE_IMAGE_H
