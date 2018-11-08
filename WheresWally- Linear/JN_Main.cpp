#include "stdafx.h"

#include "ReadWriteFunctions.h"

#include "JN_ReferenceImage.h"
#include "JN_MatchInfo.h"
#include "JN_Main.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

void StartImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, int n)
{
	std::cout << "Image searching (avg. 2s) ";

	int maxX = largeImg->GetImageWidth()  -  refImg->GetImageWidth(); maxX -= (maxX % refImg->GetImageWidth());
	int maxY = largeImg->GetImageHeight() - refImg->GetImageHeight(); maxY -= (maxX % refImg->GetImageHeight());

	std::vector<JN_MatchInfo> matchInfos;	// Create vector to store the most likely wally locations
	time_t now = time(0);					// Gets current time (from ctime)

	for (int y = 0; y < maxY; y+=5)
	{
		for (int x = 0; x < maxX; x+=2)
		{
			// Will return -1 if the match was poor
			double variance = refImg->CompareImage(x, y, largeImg, (matchInfos.size() == n ? matchInfos[n - 1].variance : -1.0f));	// The smaller the value, the better the match

			if (variance > 0)
			{
				bool collision = false;
				for (int i = 0; i < (int)matchInfos.size(); i++)
				{
					if (matchInfos.size() != 0 && JN_BaseImage::Collide(x, y, matchInfos[i].xOffset, matchInfos[i].yOffset, refImg->GetImageWidth(), refImg->GetImageHeight()))
					{
						break;
						collision = true;
					}
				}

				if (!collision)
				{
					matchInfos.push_back(JN_MatchInfo(x, y, variance));	// Add the object

					if ((int)matchInfos.size() > n)	// Cast: Removes the warning (Very annoying)
					{
						std::sort(matchInfos.begin(), matchInfos.end());	// Sorts ascending (best - worst)
						matchInfos.pop_back();								// Remove the worst match
					}

					x += refImg->GetImageWidth();
				}
			}
		}
	}

	std::cout << "OK\nFinished the image search in " << (time(0) - now) << "s\n\n";

	OutputImageSearchResults(largeImg, refImg, matchInfos);
}

void OutputImageSearchResults(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, std::vector<JN_MatchInfo> matchInfos)
{
	bool flag;

	for (int i = 0; i < (int)matchInfos.size(); i++)
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
	else
		std::cout << "Files\n\tFiles/FoundWally.pgm\n";
		if (matchInfos.size() > 1)
			std::cout << "\tFiles/BestMatches.pgm\n";

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

	std::cout << "Finding 5 best matches (including Wally)\n";

	/*
	int n;
	std::string line;
	std::getline(std::cin, line);
	n = (int)fmax(1, atoi(line.c_str()));
	*/

	StartImageSearch(largeImage, refImage, 5);	// Start the image search process
	std::cin.get();								// Pause program so output can be seen

	return 0;
}

