#ifndef JN_MATCH_INFO_H
#define JN_MATCH_INFO_H

struct JN_MatchInfo
{
public:
	// Default constructor
	JN_MatchInfo() {

	}

	JN_MatchInfo(int xOffset, int yOffset, double difference)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->difference = difference;
	}

	// Copy constructor
	JN_MatchInfo& JN_MatchInfo::operator = (const JN_MatchInfo& other) {
		this->xOffset = other.xOffset;
		this->yOffset = other.yOffset;
		this->difference = other.difference;
		return *this;
	}

public:
	int xOffset;
	int yOffset;
	double difference;

	// Overloading the greater than sign
	bool operator < (const JN_MatchInfo &other)
	{
		return difference < other.difference;
	}

	// Overloading the less than sign
	bool operator > (const JN_MatchInfo &other)
	{
		return difference > other.difference;
	}
};

#endif // !JN_MATCH_INFO_H