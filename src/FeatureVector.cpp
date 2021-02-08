#include "../inc/FeatureVector.h"

FeatureVector::FeatureVector(vector<double> vector) {
    m_vector = vector;
    m_norme = norme();
}

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

double FeatureVector::operator*(FeatureVector* B) {
    // a scalar b = sum(a[i]*b[i]) with i = {0,n}
    FeatureVector* A = this;
    double r = 0;
    for (int i = 0; i < A->getSize(); i++) {
        r += (*A)[i] * (*B)[i];
    }
    return r;
}