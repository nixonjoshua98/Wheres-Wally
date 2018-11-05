


#include "stdafx.h"
#include "JN_ReferenceImage.h"

#include <iostream>

JN_ReferenceImage::JN_ReferenceImage()
{
	// Default constructor
}

JN_ReferenceImage::JN_ReferenceImage(int w, int h, double *data)
{
	JN_BaseImage::SetImage(w, h, data);
}

JN_ReferenceImage::~JN_ReferenceImage()
{
	// Deconstructor
}

double JN_ReferenceImage::CompareImage(int offsetX, int offsetY, JN_LargeImage *compareTo, double worstBestVariance)
{
	double difference = 0.0;
	double ref = 0.0;
	double lrg = 0.0;

	for (int y = 0; y < imgH; y++)
	{
		for (int x = 0; x < imgW; x++)
		{
			ref = GetIndex(x, y);
			lrg = compareTo->GetIndex(offsetX + x, offsetY + y);

			if (ref < 255)	// Ignore white spots (Makes the result biased)
				difference += (lrg - ref) * (lrg - ref);

			if (worstBestVariance > -1.0f && difference >= worstBestVariance)
				return -1;
		}
	}

	return difference;
}