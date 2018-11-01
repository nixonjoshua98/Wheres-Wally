#ifndef JN_LARGE_IMAGE_H
#define JN_LARGE_IMAGE_H

#include "JN_BaseImage.h"

class JN_LargeImage : public JN_BaseImage
{
public:
	JN_LargeImage();	// Default constructor
	~JN_LargeImage();	// Deconstructor

	double* GetSection(int offsetX, int offsetY, int w, int h);	// Get part of the image
};

#endif // !JN_LARGE_IMAGE_H
