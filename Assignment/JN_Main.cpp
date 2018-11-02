


#include "stdafx.h"

#include "ReadWriteFunctions.h"


#include "JN_ReferenceImage.h"
#include "JN_MatchInfo.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

/*
LO1:	1st
LO2:	1st
LO3:	N/A

Best Time: 108s

TODO:
	Virtual methods, matrix operator overloads & commenting

I edited the given source files to have a reference flag (DefaultSources/ReadWriteFunctions.cpp)
*/



void StartImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, int n)
{
	std::cout << "Started image search";

	std::vector<JN_MatchInfo> matchInfos;	// Create vector to store the most likely wally locations
	time_t now = time(0);					// Gets current time (from ctime)

	int maxX = largeImg->GetImageWidth()  - refImg->GetImageWidth();
	int maxY = largeImg->GetImageHeight() - refImg->GetImageHeight();

	float percent = 0.0f;

	int y;

	for  (int x = 0; x < maxX; x++)
	{
		for (y = 0; y < maxY; y++)
		{
			// The smaller the value, the better the match
			float variance = refImg->CompareImage(x, y, largeImg);

			matchInfos.insert(matchInfos.end(), JN_MatchInfo(x, y, variance));

			// Cast: Removes the warning (Very annoying)
			if (matchInfos.size() > (unsigned int)n)
			{
				std::sort(matchInfos.begin(), matchInfos.end());	// Sorts ascending (best - worst)
				matchInfos.erase(matchInfos.end() - 1);				// Remove the worst match
			}
		}

		// Update the virtual progress bar every 5%
		int p = (float)x * y / (maxX * (float)maxY) * 100.0f;
		if (x > 0 && p >= percent + 5 || p >= 99)
		{
			percent = ceil(p);
			std::system("cls");	// Will only work on windows
			std::cout << "Search Progress: " << percent << "%";
		}
	}

	std::system("cls");

	std::cout << std::endl;
	std::cout << "Finished the image search in " << (time(0) - now) << "s\n\n";

	bool flag;

	for (int i = 0; i < n; i++)
	{
		largeImg->CreateBorderAround(matchInfos[i].xOffset, matchInfos[i].yOffset, JN_BaseImage::REF_IMG_W, JN_BaseImage::REF_IMG_H, 2, 0);

		if (i == 0)
		{
			std::cout << "Wally: " << "(" << matchInfos[i].xOffset << ", " << matchInfos[i].yOffset << ")\n";
			WritePGM("Files/FoundWally.pgm", largeImg->GetImage(), JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, 255, flag);
			continue;
		}

		std::cout << "Match #" << i << " (" << matchInfos[i].xOffset << ", " << matchInfos[i].yOffset << ")\n";
	}

	WritePGM("Files/BestMatchs.pgm", largeImg->GetImage(), JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, 255, flag);

	std::cout << std::endl;

	if (!flag)
		std::cout << "Files could not be saved\n";

	std::cout << "\n- - - Program End - - -\n";
}


int main()
{
	std::cout << "Loading images";

	// Flags which will be used to check image status
	bool refLoaded   = true;
	bool largeLoaded = true;


	// Creates the two image objects
	JN_ReferenceImage *refImage = new JN_ReferenceImage();
	JN_LargeImage *largeImage   = new JN_LargeImage();


	// Gets current time (from ctime)
	time_t t = time(0);


	// Loads the images into memory
	double *refImgData   = ReadText(     "Files/Wally_grey.txt",   JN_BaseImage::REF_IMG_W,     JN_BaseImage::REF_IMG_H, refLoaded);
	double *largeImgData = ReadText("Files/Cluttered_scene.txt", JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, largeLoaded);

	t = time(0) - t;

	// Assign the images to the relavant objects
	refImage->SetImage(    JN_BaseImage::REF_IMG_W,   JN_BaseImage::REF_IMG_H,   refImgData);
	largeImage->SetImage(JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, largeImgData);


	// If either of the images failed to load then an error has occurred
	if (!(refLoaded && largeLoaded))
	{
		std::cout << "...Images failed to load - Exiting with code -1";
		return -1;
	}

	std::cout << "...Images loaded (" << t << "s)\n";

	int n;
	std::string line;

	std::cout << "Find n number of matches (including Wally): ";
	std::getline(std::cin, line);
	n = fmax(1, atoi(line.c_str()));
	std::cout << "Looking for " << n << " match(s)\n";

	StartImageSearch(largeImage, refImage, n);	// Start the image search process

	std::cin.get();							// Pause program so output can be seen

	return 0;
}

