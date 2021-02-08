#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class FeatureVector
{
public:
    FeatureVector(vector<double> vector);
    double getNorme() const;
    int getSize() const;
    double& operator [](int i) {return m_vector[i];}
    double operator *(FeatureVector* B);

private:
    double norme();
    double m_norme;
    std::vector<double> m_vector;
};

#endif