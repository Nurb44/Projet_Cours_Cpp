#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <vector>
#include "Data.h"

class Knn
{
    public:
    Knn();
    int predict(Data d, FeatureVector f, const unsigned int k);

    protected:
    virtual int* predictSingle(unsigned int k, std::vector<double> cos, Data d);
    virtual std::vector<double> similarity(Data d, FeatureVector f);
};

#endif