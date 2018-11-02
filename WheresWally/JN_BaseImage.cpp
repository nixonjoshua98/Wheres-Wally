


#include "stdafx.h"

#include "JN_Matrix.h"
#include "JN_BaseImage.h"

JN_BaseImage::JN_BaseImage()
{
	// Default constructor
}

JN_BaseImage::~JN_BaseImage()
{
	// Deconstructor
}


JN_BaseImage::JN_BaseImage(int w, int h, double *data)
{
	// Constructor overload which takes the data
	SetImage(w, h, data);
}


// Set the attributes of the image and matrix
void JN_BaseImage::SetImage(int w, int h, double *data)
{
	imgW = w;
	imgH = h;
	img = new JN_Matrix(w, h, data);
}


// Return the matrix container
double* JN_BaseImage::GetImage()
{
	return img->GetContainer();
}


// Get index at i on the image
double JN_BaseImage::GetIndex(int i)
{
	return img->GetIndex(i);
}


// Overload method which takes x and y to get 1 pixel
double JN_BaseImage::GetIndex(int x, int y)
{
	return img->GetIndex(x, y);
}