

#include "stdafx.h"

#include "JN_Matrix.h"


// Default constructor
JN_Matrix::JN_Matrix()
{

}


JN_Matrix::JN_Matrix(int w, int h, double *data)
{
	// Creates the 2D matrix
	this->container = new double[w * h];
	width  = w;
	height = h;
	SetData(data);
}


JN_Matrix::JN_Matrix(int w, int h)
{
	this->container = new double[w * h];
	width = w;
	height = h;
}


// De-constructor
JN_Matrix::~JN_Matrix()
{
	// De-allocate memory
	delete[] this->container;
	container = NULL;
}


void JN_Matrix::SetData(double *data)
{
	// Set data to existing container
	for (int i = 0; i < (width * height); i++)
	{
		container[i] = data[i];
	}
}


void JN_Matrix::SetData(int w, int h, double *data)
{
	// Resize the container and store new data
	delete[] this->container;
	this->container = new double[w * h];
	width  = w;
	height = h;
	SetData(data);
}


double JN_Matrix::GetIndex(int x, int y)
{
	// Get value at index
	return container[(x + (y * width))];
}


double JN_Matrix::GetIndex(int i)
{
	// Get value at index
	return container[i];
}


void JN_Matrix::SetIndex(int x, int y, double v)
{
	// Set value at index
	container[x + (width * y)] = v;
}


double* JN_Matrix::GetContainer()
{
	return container;
}


JN_Matrix& JN_Matrix::operator *= (const JN_Matrix& other)
{
	JN_Matrix temp = JN_Matrix(other.width, other.height);

	for (int x = 0; x < temp.width; x++)
	{
		for (int y = 0; y < temp.height; y++)
			temp.SetIndex(x, y, this->GetIndex(x, y) * other.container[(y * other.height) + x]);
	}

	return temp;
}


JN_Matrix* JN_Matrix::operator = (const JN_Matrix& other)
{
	delete[] container;

	this->width = other.width;
	this->height = other.height;
	this->container = other.container;

	return this;
}


JN_Matrix& JN_Matrix::operator += (const JN_Matrix& other)
{
	JN_Matrix temp = JN_Matrix(other.width, other.height);

	for (int x = 0; x < temp.width; x++)
	{
		for (int y = 0; y < temp.height; y++)
			temp.SetIndex(x, y, this->GetIndex(x, y) + other.container[(y * other.height) + x]);
	}

	return temp;
}


JN_Matrix& JN_Matrix::operator -= (const JN_Matrix& other)
{
	JN_Matrix temp = JN_Matrix(other.width, other.height);

	for (int x = 0; x < temp.width; x++)
	{
		for (int y = 0; y < temp.height; y++)
			temp.SetIndex(x, y, this->GetIndex(x, y) - other.container[(y * other.height) + x]);
	}

	return temp;
}


JN_Matrix& JN_Matrix::operator /= (const JN_Matrix& other)
{
	JN_Matrix temp = JN_Matrix(other.width, other.height);

	for (int x = 0; x < temp.width; x++)
	{
		for (int y = 0; y < temp.height; y++)
			temp.SetIndex(x, y, this->GetIndex(x, y) / other.container[(y * other.height) + x]);
	}

	return temp;
}