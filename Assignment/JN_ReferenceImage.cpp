


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

float JN_ReferenceImage::CompareImage(int offsetX, int offsetY, JN_LargeImage *compareTo)
{
	float difference = 0.0f;

	for (int x = 0; x < imgH; x++)
	{
		for (int y = 0; y < imgW; y++)
		{
			double ref = GetIndex(x, y);
			double lrg = compareTo->GetIndex(x + offsetX, y + offsetY);

			if (ref < 255)	// Ignore white spots (Makes the result biased)
				difference += (lrg - ref) * (lrg - ref);
		}
	}

	return difference;
}