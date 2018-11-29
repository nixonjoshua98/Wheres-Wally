#include "stdafx.h"
#include "JN_ReferenceImage.h"

#include <iostream>


// Default constructor
JN_ReferenceImage::JN_ReferenceImage()
{

}


// overload constructor
JN_ReferenceImage::JN_ReferenceImage(int w, int h, double *data)
{
	JN_BaseImage::SetImage(w, h, data);
}


// Deconstructor
JN_ReferenceImage::~JN_ReferenceImage()
{

}


// Compare two image matrix
double JN_ReferenceImage::SSDCompare(int offsetX, int offsetY, JN_LargeImage *compareTo, double worstBest)
{
	double difference = 0.0;
	double ref = 0.0;
	double lrg = 0.0;

	for (int y = 0; y < imgH; y += 3 )
	{
		for (int x = 0; x < imgW; x += 2)
		{
			ref = GetIndex(x, y);
			lrg = compareTo->GetIndex(offsetX + x, offsetY + y);

			if (ref < 255)	// Ignore white spots (Makes the result biased)
				// Sum of squared difference
				difference += (lrg - ref) * (lrg - ref);

			if (worstBest > -1.0f && difference >= worstBest)
				return -1;
		}
	}

	return difference;
}


bool JN_ReferenceImage::CorrectWidth()
{
	return imgW == REF_IMG_W;
}


bool JN_ReferenceImage::CorrectHeight()
{
	return imgH == REF_IMG_H;
}