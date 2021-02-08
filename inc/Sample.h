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
    int getTag() const;
    double& operator [](int i) {return (*m_features)[i];}
    FeatureVector *getFeature() const;
    std::string getString() const;

private:
    int m_tag;
    FeatureVector *m_features;
};

#endif