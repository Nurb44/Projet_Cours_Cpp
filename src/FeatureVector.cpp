#include "../inc/FeatureVector.h"

FeatureVector::FeatureVector(vector<double> *vector) {
    m_vector = *vector;
    m_norme = norme();
}

FeatureVector::FeatureVector(std::string features) {
    // FeatureVector accept a string with features "feature_one feature_two ..."

    std::string temp_sval = ""; // temporary string value
    double temp_dval; // temporary double value

    // Iterate through all characters of the string
    for (auto it = features.cbegin(); it != features.cend(); ++it) {
        // If character is different of simple space
        // Concatenate with previous
        if (*it != *" ") {
            temp_sval = temp_sval + *it;
        }
        // If last character or space
        // Convert into double and save at back of the vector
        if (*it == *" " or it == features.cend() - 1) {
            temp_dval = std::stod(temp_sval);
            m_vector.push_back(temp_dval);
            temp_sval = "";
        }
    }
    // Calculate the norm
    m_norme = norme();

}

FeatureVector::~FeatureVector() {

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

    // Scalar product of A and B : (|A+B|² - |A|² - |B|²) / 2
    double total = 0; // used to calculate scalar product

    int i;
    // Calculate total = |A+B|²
    for (i = 0; i < A.getSize(); i++) {
        total += pow(A[i] + B[i], 2);
    }

    // Calculate total = (total - |A|² - |B|²)
    total = total - pow(A.getNorme(), 2) - pow(B.getNorme(), 2);

    // Calculate total = total / 2
    total = total / 2;
    return total;
}