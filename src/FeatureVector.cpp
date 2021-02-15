#include "../inc/FeatureVector.h"

/**
 * Constructor FeatureVector.
 *
 * @param Vector Container of features.
 */
FeatureVector::FeatureVector(vector<double> vector) {
    m_vector = std::move(vector);
    m_norme = norme();
}

/**
 * Calculate the norm of the vector.
 *
 * @return Norm of the vector.
 */
double FeatureVector::norme() {
    // norm = square root of the sum of squares
    double total = 0;
    for (const auto &value: m_vector) {
        //cout << value << endl;
        total += pow(value, 2);
    }
    m_norme = sqrt(total);
    return sqrt(total);
}

/**
 * Accessor of m_norme.
 *
 * @return Norm of the vector.
 */
double FeatureVector::getNorme() const {
    return m_norme;
}

/**
 * Accessor of m_vector size.
 *
 * @return Size of the vector.
 */
int FeatureVector::getSize() const {
    return m_vector.size();
}

/**
 * Calculate scalar product between two FeatureVector.
 *
 * @param B Pointer to a FeatureVector.
 * @return Scalar product result.
 */
double FeatureVector::operator*(FeatureVector *B) {
    // a scalar b = sum(a[i]*b[i]) with i = {0;n}, n = m_vector.size()
    FeatureVector *A = this;
    double r = 0;
    for (int i = 0; i < A->getSize(); i++) {
        r += (*A)[i] * (*B)[i];
    }
    return r;
}