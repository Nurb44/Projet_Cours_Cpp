#include "../inc/Sample.h"

Sample::Sample(int tag)
{
    m_tag = tag;
}

Sample::~Sample()
{
    
}

int Sample::getTag()
{
    return m_tag;
}

FeatureVector Sample::getFeatureVector()
{
    return m_feature;
}