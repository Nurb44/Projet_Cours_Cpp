#include "../inc/Sample.h"

Sample::Sample(int t, FeatureVector* f)
{
    m_tag = t;
    m_features = f;
}

Sample::~Sample()
{
    delete m_features;
}

int Sample::getTag()
{
    return m_tag;
}

FeatureVector Sample::getFeature()
{
    return *m_features;
}

string Sample::getString() {
    std::string str = "";
    str += "Tag : " + std::to_string(m_tag) + "; ";
    str += "Norme : " + std::to_string(m_features->getNorme());
    return str;
}