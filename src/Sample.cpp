#include "../inc/Sample.h"

Sample::Sample(int t, FeatureVector* f)
{
    m_tag = t;
    m_features = f;
}

Sample::Sample(Sample &s) {
    m_tag = s.m_tag;
    m_features = new FeatureVector(*s.m_features);
}

Sample::~Sample()
{
    delete m_features;
}

int Sample::getTag() const {
    return m_tag;
}

FeatureVector *Sample::getFeature() const {
    return m_features;
}

    std::string str = "";
    str += "Tag : " + std::to_string(m_tag) + "; ";
string Sample::getString() const {
    str += "Norme : " + std::to_string(m_features->getNorme());
    return str;
}