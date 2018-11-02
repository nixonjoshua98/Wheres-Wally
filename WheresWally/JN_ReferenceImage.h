#ifndef JN_REFERENCE_IMAGE_H
#define JN_REFERENCE_IMAGE_H

#include "JN_BaseImage.h"
#include "JN_LargeImage.h"

class JN_ReferenceImage : public JN_BaseImage
{
public:
	JN_ReferenceImage();								// Default constructor
	JN_ReferenceImage(int w, int h, double *data);		// Constructor overload
	~JN_ReferenceImage();								// Deconstructor

	/*
	Compares the image to a section of the large image, it will stop looping as soon as the variance
	has become worst variance ever. This caused my program to go from 110s to 45s (on my PC)
	which is impressive for a linear search
	*/
	double CompareImage(int offsetX, int offsetY, JN_LargeImage *compareTo, double worstBestVariance);
};

#endif // !JN_REFERENCE_IMAGE_H
