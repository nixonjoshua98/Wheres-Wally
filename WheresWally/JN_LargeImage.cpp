


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


// Return part of the image
double* JN_LargeImage::GetSection(int offsetX, int offsetY, int w, int h)
{
	double* section = new double[w * h];
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
			section[x + (y * w)] = GetIndex(offsetX + x, offsetY + y);
	}
	return section;
}


// Set a pixel of the image
void JN_LargeImage::SetIndex(int x, int y, double v)
{
	img->SetIndex(x, y, v);
}

void JN_LargeImage::CreateBorderAround(int xOffset, int yOffset, int w, int h, int thickness, double v)
{
	// Creates a black border aroudn the raneg given, higher thickness will cut into the image
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (x < thickness || y < thickness || y + thickness >= h || x + thickness >= w)
				SetIndex(x + xOffset, y + yOffset, v);
		}
	}
}