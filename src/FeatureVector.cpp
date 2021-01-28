#include "../inc/FeatureVector.h"

FeatureVector::FeatureVector(std::string features) {
    // FeatureVector accept a string with features "feature_one feature_two ..."

    std::string temp_sval = ""; // temporary string value
    double temp_dval; // temporary double value

    double total = 0; // used to calculate the norm

    // Iterate through all characters of the string
    for (auto it = features.cbegin(); it != features.cend(); ++it) {
        // If character is different of simple space
        // Concatenate with previous
        if (*it != *" ") {
            temp_sval = temp_sval + *it;
        }
        // If last character or space
        // Convert into double
        // Add pow of it into total (to squirt at the end and get the norm)
        // Save double at back of vector
        if (*it == *" " or it == features.cend() - 1) {
            temp_dval = std::stod(temp_sval);
            total += pow(temp_dval, 2);
            m_vector.push_back(temp_dval);
            temp_sval = "";
        }
    }
    // Calculate the norm
    m_norme = sqrt(total);

}

FeatureVector::~FeatureVector() {

}

double FeatureVector::getNorme() {
    return m_norme;
}

int FeatureVector::getSize() {
    return m_vector.size();
}

double FeatureVector::operator*(FeatureVector B) {
    FeatureVector A = *this;

    // Scalar product of A and B : (|A+B|² - |A|² - |B|²) / (2 * |A| * |B|)
    double total = 0; // used to calculate scalar product


    // Calculate total = |A+B|²
    int it = 0;
    for (auto &n : m_vector) {
        total += pow(n + B[it], 2);
        it++;
    }

    // Calculate total = (total - |A|² - |B|²)
    total = total - pow(A.getNorme(), 2) - pow(B.getNorme(), 2);

    // Calculate total = total / (2 * |A| * |B|)
    total = total / (2 * A.getNorme() * B.getNorme());
    return total;
}