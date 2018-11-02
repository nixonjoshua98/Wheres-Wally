


#include "stdafx.h"

#include "JN_Matrix.h"
#include "JN_BaseImage.h"

JN_BaseImage::JN_BaseImage()
{
	// Default constructor
}

JN_BaseImage::~JN_BaseImage()
{
	// Matrix deconstructor
}

JN_BaseImage::JN_BaseImage(int w, int h, double *data)
{
	SetImage(w, h, data);
}

void JN_BaseImage::SetImage(int w, int h, double *data)
{
	imgW = w;
	imgH = h;
	img = new JN_Matrix(w, h, data);
}

double* JN_BaseImage::GetImage()
{
	return img->GetContainer();
}

double JN_BaseImage::GetIndex(int i)
{
	return img->GetIndex(i);
}

double JN_BaseImage::GetIndex(int x, int y)
{
	return img->GetIndex(x, y);
}