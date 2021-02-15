#ifndef DATA_H
#define DATA_H

#include <iostream>
#include "Sample.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <time.h>

class Data {
public:
    Data();
    Data(Data &d);
    ~Data();
    bool load_from_svm(const std::string& filepath);
    unsigned int getNbSamples() const;
    string getString() const;
    Sample *&operator[](int i) { return (m_data)[i]; }
    Data *split(unsigned int ratio);
    void shuffle();

private:
    std::vector<Sample *> m_data;
    unsigned int m_nb_features;
    unsigned int m_nb_samples;
};

#endif