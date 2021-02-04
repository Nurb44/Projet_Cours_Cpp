#ifndef DATA_H
#define DATA_H

#include <iostream>
#include "Sample.h"
#include <fstream>

class Data
{
public:
    Data();
    ~Data();
    void load_from_svm(std::string filepath);
    int getNbSamples();
    string getString();
    void scale();
    Sample*& operator [](int i) {return (m_data)[i];}


private:
    std::vector<Sample*> m_data;
    int m_nb_features;
    int m_nb_samples;
};

#endif