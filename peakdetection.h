#ifndef PEAKDETECTION_H
#define PEAKDETECTION_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define EPS 2.2204e-16

using namespace std;

void findPeaks(vector<float> x0, vector<int>& peakInds);


#endif // PEAKDETECTION_H
