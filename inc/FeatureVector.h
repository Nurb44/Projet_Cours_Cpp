#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <vector>

class FeatureVector
{
public:
    FeatureVector();
    ~FeatureVector();
    int getNbFeature();
    double getFeature(unsigned int index);
    std::vector<double*> getFeatureVector();

private:
    int m_nbFeature;
    std::vector<double*> m_feature;
};

#endif