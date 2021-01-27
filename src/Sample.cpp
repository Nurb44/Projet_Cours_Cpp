#include "../inc/Sample.h"

Sample::Sample(std::string sample)
{
    // Tag is the first character
    m_tag = stoi(&sample.at(0));

    // We can delete first and second and send it to feature vector
    sample.erase(0,2);
    m_features = new FeatureVector(sample);
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