#include "../inc/Sample.h"

/**
 * Constructor Sample.
 *
 * @param t Tag of the sample.
 * @param f Pointer to a FeatureVector.
 */
Sample::Sample(int t, FeatureVector *f) {
    m_tag = t;
    m_features = f;
}

/**
 * Copy constructor Sample.
 *
 * @param s Reference to a Sample.
 */
Sample::Sample(Sample &s) {
    m_tag = s.m_tag;
    m_features = new FeatureVector(*s.m_features);
}

/**
 * Destructor Sample.
 */
Sample::~Sample() {
    delete m_features;
}

/**
 * Accessor of m_tag.
 *
 * @return tag of the Sample.
 */
int Sample::getTag() const {
    return m_tag;
}

/**
 * Accessor of m_features.
 *
 * @return FeatureVector pointer.
 */
FeatureVector *Sample::getFeature() const {
    return m_features;
}

/**
 * Give string representation of the Sample.
 *
 * @return String representation of the Sample.
 */
string Sample::getString() const {
    std::string str;
    str = "Tag : " + std::to_string(m_tag) + "; ";
    str += "Norme : " + std::to_string(m_features->getNorme());
    return str;
}