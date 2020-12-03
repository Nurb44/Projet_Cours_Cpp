#include "../inc/Data.h"

Data::Data()
{
    m_nb_features = 0;
    m_nb_samples = 0;
}

Data::~Data()
{
    // TODO : Destructor method
}

void Data::add()
{
    // TODO : Add sample into data array
}

void Data::aspire_les_donnees(std::string filepath)
{
    // TODO : Import data from file
}

void Data::load()
{
    // TODO : Function to define
}

int Data::getNbSamples()
{
    return m_nb_samples;
}

char* Data::getString()
{
    // TODO : Give str representation
}
