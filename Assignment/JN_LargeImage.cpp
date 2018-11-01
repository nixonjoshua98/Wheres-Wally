


#include "stdafx.h"
#include "JN_LargeImage.h"

JN_LargeImage::JN_LargeImage()
{
	// Default constructor
}

JN_LargeImage::~JN_LargeImage()
{
	// Deconstructor
}

double* JN_LargeImage::GetSection(int offsetX, int offsetY, int w, int h)
{
	double* section = new double[w * h];
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			section[x + (y * w)] = GetIndex(offsetX + x, offsetY + y);
		}
	}
	return section;
}