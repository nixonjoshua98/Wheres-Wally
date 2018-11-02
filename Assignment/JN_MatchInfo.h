#ifndef JN_MATCH_INFO_H
#define JN_MATCH_INFO_H

struct JN_MatchInfo
{
public:
	JN_MatchInfo(int xOffset, int yOffset, float variance)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this-> variance = variance;
	}

public:
	int xOffset;
	int yOffset;
	float variance;

	// Overloading the greater than sign
	bool operator < (const JN_MatchInfo &other)
	{
		return variance < other.variance;
	}

	// Overloading the less than sign
	bool operator > (const JN_MatchInfo &other)
	{
		return variance > other.variance;
	}
};

#endif // !JN_MATCH_INFO_H
