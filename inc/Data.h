#ifndef DATA_H
#define DATA_H

#include <iostream>
#include "Sample.h"
#include <fstream>

class Data {
public:
    Data();
    Data(Data &d);
    ~Data();
    bool load_from_svm(std::string filepath);
    int getNbSamples() const;
    string getString() const;
    Sample *&operator[](int i) { return (m_data)[i]; }
    Data *split(unsigned int ratio);

private:
    std::vector<Sample *> m_data;
    int m_nb_features;
    int m_nb_samples;
};

#endif