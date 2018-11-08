#ifndef JN_MAIN_H
#define JN_MAIN_H

#include "JN_LargeImage.h"
#include "JN_ReferenceImage.h"
#include "JN_MatchInfo.h"

#include <vector>

void StartImageSearch(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, int n);
void OutputImageSearchResults(JN_LargeImage *largeImg, JN_ReferenceImage *refImg, std::vector<JN_MatchInfo> matchInfos);

#endif // !JN_MAIN_H
