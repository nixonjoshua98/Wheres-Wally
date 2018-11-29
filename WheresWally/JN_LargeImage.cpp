


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
			section[x + (y * w)] = GetIndex(offsetX + x, offsetY + y);
	}
	return section;
}


void JN_LargeImage::SetIndex(int x, int y, double v)
{
	img->SetIndex(x, y, v);
}


void JN_LargeImage::CreateBorderAround(int xOffset, int yOffset, int w, int h, int thickness, double v)
{
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (x < thickness || y < thickness || y + thickness >= h || x + thickness >= w)
				SetIndex(x + xOffset, y + yOffset, v);
		}
	}
}


bool JN_LargeImage::CorrectWidth()
{
	return imgW == LARGE_IMG_W;
}


bool JN_LargeImage::CorrectHeight()
{
	return imgH == LARGE_IMG_H;
}