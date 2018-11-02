


#include "stdafx.h"

#include "JN_Main.h"
#include "ReadWriteFunctions.h"

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>

/*
LO1:	1st
LO2:	1st
LO3:	N/A

Best Time: 108s | 45s

TODO:
	Virtual methods, matrix operator overloads & commenting

I edited the given source files to have a reference flag (DefaultSources/ReadWriteFunctions.cpp)
*/



void StartImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, int n)
{
	std::cout << "Started image search";

	std::vector<JN_MatchInfo> *matchInfos = new std::vector<JN_MatchInfo>;	// Create vector to store the most likely wally locations
	time_t now = time(0);													// Gets current time (from ctime)
	int maxX = largeImg->GetImageWidth()  - refImg->GetImageWidth();		// The max X value, used for the loop and the progress report
	int maxY = largeImg->GetImageHeight() - refImg->GetImageHeight();		// The max Y value, used for the loop and the progress report
	int percent = 0;	// Search percent complete
	int y = 0;			// Declaration needed to be outside the y loop scope so could use it in the x loop
	double variance;	// Will store the variance of the current image being looked at

	for  (int x = 0; x < maxX; x++)
	{
		for (y = 0; y < maxY; y++)
		{
			// The smaller the value, the better the match
			variance = refImg->CompareImage(x, y, largeImg, (matchInfos->size() == n ? matchInfos->at(n - 1).variance : -1.0f));

			// If the variance is worse than the existing worse, then just ignore it
			if (variance == -1)
				continue;

			// Insert the new variance into the vector
			matchInfos->insert(matchInfos->end(), JN_MatchInfo(x, y, variance));

			// Cast: Removes the warning (Very annoying)
			if (matchInfos->size() > (unsigned int)n)
			{
				// Sort the vector so i can remove the worst variance
				std::sort(matchInfos->begin(), matchInfos->end());	// Sorts ascending (best - worst)
				matchInfos->erase(matchInfos->end() - 1);				// Remove the worst match
			}
		}

		// Update the virtual progress bar every 5%
		float p = (float)x * y / (maxX * (float)maxY) * 100.0f;
		if (x > 0 && p >= percent + 5)
		{
			percent = (int)floor(p);
			std::system("cls");	// Will only work on windows
			std::cout << "Search Progress: " << percent << "%\n";
		}
	}

	std::system("cls");																// Will only work on windows
	std::cout << "Finished the image search in " << (time(0) - now) << "s\n\n";		// Output the search time

	OutputImageSearchResults(largeImg, refImg, matchInfos);
}

void OutputImageSearchResults(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, std::vector<JN_MatchInfo> *matchInfos)
{
	bool flag;

	// Unsigned to remove warning
	for (unsigned int i = 0; i < matchInfos->size(); i++)
	{
		// Highlights wally match
		largeImg->CreateBorderAround(matchInfos->at(i).xOffset, matchInfos->at(i).yOffset, JN_BaseImage::REF_IMG_W, JN_BaseImage::REF_IMG_H, 2, 0);

		if (i == 0)
		{
			// First in the vector is always the best wally match
			std::cout << "Wally: " << "(" << matchInfos->at(i).xOffset << ", " << matchInfos->at(i).yOffset << ")\n";
			// Just wally in this image
			WritePGM("Files/FoundWally.pgm", largeImg->GetImage(), JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, 255, flag);
			continue;
		}

		std::cout << "Match #" << i << " (" << matchInfos->at(i).xOffset << ", " << matchInfos->at(i).yOffset << ")\n";
	}

	// Write all of the matches to this file
	WritePGM("Files/BestMatchs.pgm", largeImg->GetImage(), JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, 255, flag);

	std::cout << std::endl;

	if (!flag)	// Error flag
		std::cout << "Files could not be saved\n";
	else
		std::cout << "Files saved at\n\tFiles/FoundWally.pgm\n\tFiles/BestMatches.pgm\n\n";


	delete matchInfos;

	std::cout << "- - - Program End - - -\n";
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
	n = (int)fmax(1, atoi(line.c_str()));
	std::cout << "Looking for " << n << " match(s)\n";

	StartImageSearch(largeImage, refImage, n);	// Start the image search process
	std::cin.get();								// Pause program so output can be seen

	return 0;
}

