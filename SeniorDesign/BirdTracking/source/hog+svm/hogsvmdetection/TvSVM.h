#ifndef TvSVM_H
#define TvSVM_H

//#include "ml.h"
#include "opencv2/opencv.hpp"

using namespace std;

class TvSVM :
    public CvSVM
{
public:
    TvSVM(void);
    ~TvSVM(void);
    vector<float> get_linear_weight(void);
};


#endif
