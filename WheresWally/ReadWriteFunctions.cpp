


#include "stdafx.h"

#include "ReadWriteFunctions.h"

#include <fstream>
#include <iostream>

double* ReadText(char *fileName, int matrixWidth, int matrixHeight, bool &flag)
{
	flag = true;
	double* data = new double[matrixHeight * matrixWidth];
	int i = 0;
	std::ifstream f(fileName);

	if (f.is_open())
	{
		while (f.good())
		{
			if (i > matrixHeight * matrixWidth - 1) break;
			f >> *(data + i);
			i++;
		}
		f.close();
	}
	else
	{
		std::cout << "File not opened Z\n";
		flag = false;
	}
	return data;
}


// Use Q = 255 for greyscale images and 1 for binary images.
void WritePGM(char *fileName, double *data, int matrixWidth, int matrixHeight, int Q, bool &flag)
{
	unsigned char *image;
	std::ofstream f;
	flag = true;

	image = (unsigned char *) new unsigned char[matrixWidth * matrixHeight];

	for (int i = 0; i < matrixWidth * matrixHeight; i++)
		image[i] = (unsigned char)data[i];

	f.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!f.is_open())
	{
		delete[] image;
		flag = false;
	}

	f << "P5" << std::endl << matrixWidth << " " << matrixHeight << std::endl << Q << std::endl;

	f.write(reinterpret_cast<char *>(image), (matrixWidth * matrixHeight) * sizeof(unsigned char));

	if (f.fail())
		flag = false;

	f.close();

	delete[] image;
}