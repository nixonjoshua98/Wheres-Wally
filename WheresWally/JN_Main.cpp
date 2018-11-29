#include "stdafx.h"

#include "ReadWriteFunctions.h"

#include "JN_ReferenceImage.h"
#include "JN_MatchInfo.h"
#include "JN_Main.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>

/*
	PASS:	Data is passed around etc.					COMPLETE
	2:2:	Vectors, pointers, wally is found			COMPLETE
	2:1:	Wally is found, pass by reference etc.		COMPLETE
	1st:	N-best list									COMPLETE

	PASS:	Variables, structures						COMPLETE
	2:2:	Inheritance									COMPLETE
	2:1:	Acessibility								COMPLETE
	1st:	Virtual, matrix overloading					COMPLETE
*/

void StartImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, int n)
{
	std::cout << "Image searching";

	int maxX = largeImg->GetImageWidth() - refImg->GetImageWidth(); maxX -= (maxX % refImg->GetImageWidth());
	int maxY = largeImg->GetImageHeight() - refImg->GetImageHeight(); maxY -= (maxX % refImg->GetImageHeight());

	std::vector<JN_MatchInfo> matchInfos;			// Create vector to store the most likely wally locations
	auto start = std::chrono::system_clock::now();	// Time at start

	for (int y = 0; y < maxY; y += 5)
	{
		for (int x = 0; x < maxX; x += 2)
		{
			// Will return -1 if the match was poor
			double difference = refImg->SSDCompare(x, y, largeImg, (matchInfos.size() == n ? matchInfos[n - 1].difference : -1.0f));	// The smaller the value, the better the match

			if (difference > 0)
			{
				matchInfos.push_back(JN_MatchInfo(x, y, difference));	// Add the object

				if ((int)matchInfos.size() > n)	// Cast: Removes the warning (Very annoying)
				{
					std::sort(matchInfos.begin(), matchInfos.end());	// Sorts ascending (best - worst)
					matchInfos.pop_back();								// Remove the worst match
				}

				x += refImg->GetImageWidth();
			}
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> span = end - start;

	std::cout << "...OK\nFinished the image search in " << span.count() << "ms\n\n";

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
	bool refLoaded = true;
	bool largeLoaded = true;


	// Creates the two image objects
	JN_ReferenceImage *refImage = new JN_ReferenceImage();
	JN_LargeImage *largeImage = new JN_LargeImage();


	// Gets current time
	auto start = std::chrono::system_clock::now();


	// Loads the images into memory
	double *refImgData = ReadText("Files/Wally_grey.txt", JN_BaseImage::REF_IMG_W, JN_BaseImage::REF_IMG_H, refLoaded);
	double *largeImgData = ReadText("Files/Cluttered_scene.txt", JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, largeLoaded);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> span = end - start;

	// Assign the images to the relavant objects
	refImage->SetImage(JN_BaseImage::REF_IMG_W, JN_BaseImage::REF_IMG_H, refImgData);
	largeImage->SetImage(JN_BaseImage::LARGE_IMG_W, JN_BaseImage::LARGE_IMG_H, largeImgData);


	// If either of the images failed to load then an error has occurred
	if (!(refLoaded && largeLoaded))
	{
		std::cout << "...Images failed to load - Exiting with code -1";
		return -1;
	}

	std::cout << "...Images loaded (" << span.count() << "ms)\n";

	int n;
	std::string line;
	std::cout << "N-matches: ";
	std::getline(std::cin, line);
	n = (int)fmax(1, atoi(line.c_str()));

	std::cout << "Finding " << n << " best matches (including Wally)\n";

	StartImageSearch(largeImage, refImage, n);	// Start the image search process
	std::cin.get();								// Pause program so output can be seen

	return 0;
}
