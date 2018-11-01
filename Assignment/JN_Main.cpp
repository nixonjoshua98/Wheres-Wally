


#include "stdafx.h"
#include "JN_ReferenceImage.h"
#include "JN_LargeImage.h"

#include <iostream>
#include <ctime>

/*
LO1:	Pass
LO2:	1st


Best Time: 109s

I edited the given source files to have a reference flag (GivenSources/ReadWriteFunctions.cpp)
*/

struct Offset
{
	int x;
	int y;
};

void DoImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg)
{
	std::cout << "Started search";

	time_t now = time(0);

	float bestVariance     = NULL;
	float currentVariance  = 0.0f;
	Offset bestOffset      = Offset();

	for (int x = 0; x < (largeImg->imgW - refImg->imgW); x++)
	{
		for (int y = 0; y < (largeImg->imgH - refImg->imgH); y++)
		{
			currentVariance = refImg->CompareImage(x, y, largeImg);

			if (currentVariance < bestVariance || bestVariance == NULL)
			{
				bestVariance = currentVariance;
				bestOffset   = Offset({ x, y });
			}
		}
	}

	std::cout << "...Finished the image search in " << (time(0) - now) << "s\n";

	bool flag = true;
	JN_BaseImage::Output2PGM("Files/BestMatch.pgm", refImg->imgW, refImg->imgH, largeImg->GetSection(bestOffset.x, bestOffset.y, refImg->imgW, refImg->imgH), flag);

	if (flag)
		std::cout << "Best match saved as BestMatch.pgm\n";

	std::cout << bestOffset.x << ", " << bestOffset.y << std::endl;
}


int main()
{
	std::cout << "Loading images";
	bool refLoaded = true, largeLoaded = true;

	JN_ReferenceImage *refImage = new JN_ReferenceImage();
	JN_LargeImage *largeImage   = new JN_LargeImage();

	refImage->SetImage(36, 49, JN_BaseImage::ReadTextFile("Files/Wally_grey.txt", 36, 49, refLoaded));
	largeImage->SetImage(1024, 768, JN_BaseImage::ReadTextFile("Files/Cluttered_scene.txt", 1024, 768, largeLoaded));

	if (!(refLoaded && largeLoaded))
	{
		std::cout << "...Images failed to load - Exiting with code -1";
		return -1;
	}

	std::cout << "...Images loaded correctly (2/2)\n";

	DoImageSearch(largeImage, refImage);

	std::cin.get();

	return 0;
}

