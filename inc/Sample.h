#ifndef SAMPLE_H
#define SAMPLE_H

#include "FeatureVector.h"

class Sample
{
public:
    Sample(int tag);
    ~Sample();
    int getTag();
    FeatureVector getFeatureVector();

private:
    int m_tag;
    FeatureVector m_feature;
};

#endif