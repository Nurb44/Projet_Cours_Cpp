#ifndef SAMPLE_H
#define SAMPLE_H

#include "FeatureVector.h"
#include <iostream>

class Sample
{
public:
    Sample(int t, FeatureVector* f);
    Sample(Sample &s);
    ~Sample();
    int getTag();
    FeatureVector getFeature();
    double& operator [](int i) {return (*m_features)[i];}
    std::string getString();

private:
    int m_tag;
    FeatureVector *m_features;
};

#endif