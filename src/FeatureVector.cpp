#include "../inc/FeatureVector.h"

FeatureVector::FeatureVector()
{
    m_nbFeature = 0;
}

FeatureVector::~FeatureVector()
{

}

int FeatureVector::getNbFeature()
{
    return m_nbFeature;
}

double FeatureVector::getFeature(unsigned int index)
{
    return index < m_nbFeature ? *m_feature[index] : -1;
}

std::vector<double*> FeatureVector::getFeatureVector()
{
    return m_feature;
}