#ifndef JN_MATCH_INFO_H
#define JN_MATCH_INFO_H

struct JN_MatchInfo
{
public:
	// Default constructor
	JN_MatchInfo() {

	}

	JN_MatchInfo(int xOffset, int yOffset, double variance)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this-> variance = variance;
	}

	// Copy constructor
	JN_MatchInfo& JN_MatchInfo::operator = (const JN_MatchInfo& other) {
		this->xOffset  = other.xOffset;
		this->yOffset  = other.yOffset;
		this->variance = other.variance;
		return *this;
	}

public:
	int xOffset;
	int yOffset;
	double variance;

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
