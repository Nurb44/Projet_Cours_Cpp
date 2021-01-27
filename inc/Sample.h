#ifndef SAMPLE_H
#define SAMPLE_H

#include "FeatureVector.h"
#include <iostream>

class Sample
{
public:
    Sample(std::string features);
    ~Sample();
    int getTag();
    FeatureVector getFeature();
    double& operator [](int i) {return (*m_features)[i];}

private:
    int m_tag;
    FeatureVector *m_features;
};

#endif