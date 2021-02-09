#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <vector>
#include "Data.h"

class Knn
{
    public:
    Knn();
    unsigned int predict(Data d, FeatureVector *f, const unsigned int k, bool info = false);
    virtual unsigned int* predictSingle(unsigned int k, std::vector<double> val, Data d) = 0;
    virtual std::vector<double> similarity(Data d, FeatureVector *f) = 0;
};

#endif