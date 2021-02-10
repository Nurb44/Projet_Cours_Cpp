#ifndef KNNDISTANCE_H
#define KNNDISTANCE_H

#include <iostream>
#include <cmath>
#include <float.h>
#include "Knn.h"

class KnnDistance: public Knn
{
    public:
    KnnDistance();
    virtual unsigned int* predictSingle(const unsigned int k, std::vector<double> dist, Data d);
    virtual std::vector<double> similarity(Data d, FeatureVector *f);
};

#endif