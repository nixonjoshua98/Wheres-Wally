#ifndef JN_MATCH_INFO_H
#define JN_MATCH_INFO_H

struct JN_MatchInfo
{
public:
	JN_MatchInfo(int xOffset, int yOffset, double variance)
	{
		// Sets the values in the struct
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this-> variance = variance;
	}

	int xOffset;		// The X value where the image starts
	int yOffset;		// The Y value where the image starts
	double variance;	// The variance between the ref image and the large image (smaller is better)

	// Overloading the greater than sign
	bool operator < (const JN_MatchInfo &other)
	{
		// Overloads the sign for easy sorting by variance
		return variance < other.variance;
	}

	// Overloading the less than sign
	bool operator > (const JN_MatchInfo &other)
	{
		// Overloads the sign for easy sorting by variance
		return variance > other.variance;
	}
};

#endif // !JN_MATCH_INFO_H
