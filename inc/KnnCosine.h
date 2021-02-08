#ifndef KNNCOSINE_H
#define KNNCOSINE_H

#include <iostream>
#include "Knn.h"

class KnnCosine: public Knn
{
    public:
    KnnCosine();
    virtual int* predictSingle(const unsigned int k, std::vector<double> cos, Data d);
    virtual std::vector<double> similarity(Data d, FeatureVector f);
};

#endif