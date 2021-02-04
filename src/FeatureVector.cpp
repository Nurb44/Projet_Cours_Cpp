#include "../inc/FeatureVector.h"

FeatureVector::FeatureVector(vector<double> *vector) {
    m_vector = *vector;
    m_norme = norme();
}

FeatureVector::~FeatureVector() {}

double FeatureVector::norme() {
    double total = 0;
    for (const auto &value: m_vector) {
        total += pow(value, 2);
    }
    return sqrt(total);
}

double FeatureVector::getNorme() {
    return m_norme;
}

int FeatureVector::getSize() {
    return m_vector.size();
}

double FeatureVector::operator*(FeatureVector B) {
    FeatureVector A = *this;

    vector<double> vector;
    for (int i = 0; i < A.getSize(); i++) {
        vector.push_back(A[i] + B[i]);
    }
    FeatureVector AB(&vector);

    // Scalar product of A and B : (|A+B|² - |A|² - |B|²) / 2
    return (pow(AB.getNorme(), 2) - pow(A.getNorme(), 2) - pow(B.getNorme(), 2)) / 2;
}