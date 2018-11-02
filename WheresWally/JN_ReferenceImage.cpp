#include "stdafx.h"
#include "JN_ReferenceImage.h"

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


// Compares a matrix to another matrix
double JN_ReferenceImage::CompareImage(int offsetX, int offsetY, JN_LargeImage *compareTo, double worstBestVariance)
{
	double difference = 0.0f;

	for (int x = 0; x < imgH; x++)
	{
		for (int y = 0; y < imgW; y++)
		{
			double ref = GetIndex(x, y);
			double lrg = compareTo->GetIndex(x + offsetX, y + offsetY);

			// Grab the difference between pixels
			if (ref < 255)	// Ignore white spots (Makes the result biased)
				// Needed a large number to show the difference, squaring it increased the gap reducing close differences
				difference += (lrg - ref) * (lrg - ref);


			// This line dropped my runtime to half
			// If the current variance is already worst than the existing worst then it can be stopped as it doesn't matter
			if (worstBestVariance > -1.0f && difference >= worstBestVariance)
				return -1;
		}
	}

	return difference;
}