#ifndef JN_REFERENCE_IMAGE_H
#define JN_REFERENCE_IMAGE_H

#include "JN_BaseImage.h"
#include "JN_LargeImage.h"

class JN_ReferenceImage : public JN_BaseImage
{
public:
	JN_ReferenceImage();								// Default constructor
	JN_ReferenceImage(int w, int h, double *data);
	~JN_ReferenceImage();								// Deconstructor

	float CompareImage(int offsetX, int offsetY, JN_LargeImage *compareTo);
};

#endif // !JN_REFERENCE_IMAGE_H
