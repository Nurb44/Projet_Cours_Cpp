#ifndef DATA_H
#define DATA_H

#include <iostream>
#include "Sample.h"
#include <fstream>

class Data
{
public:
    Data();
    Data(Data &d);
    ~Data();
    int load_from_svm(std::string filepath);
    void scale();
    Sample*& operator [](int i) {return (m_data)[i];}
    Data* split(int percentage);
    void add(Sample* s);

    int getNbSamples() const;
    string getString() const;

private:
    std::vector<Sample*> m_data;
    int m_nb_features;
    int m_nb_samples;
};

#endif