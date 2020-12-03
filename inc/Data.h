#ifndef DATA_H
#define DATA_H

#include "Sample.h"
#include <iostream>

class Data
{
public:
    Data();
    ~Data();
    void add();
    void load();
    void aspire_les_donnees(std::string filepath);
    int getNbSamples();
    char *getString();

private:
    Sample *m_data;
    int m_nb_features;
    int m_nb_samples;
};

#endif