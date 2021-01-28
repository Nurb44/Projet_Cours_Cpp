#include "../inc/Data.h"

Data::Data()
{
    m_nb_features = 0;
    m_nb_samples = 0;
}

Data::~Data()
{
    for(const auto& value: m_data) {
        delete value;
    }

}

void Data::aspire_les_donnees(std::string filepath)
{
    cout << filepath << endl;
    ifstream myfile (filepath);

    string line;

    std::getline(myfile, line);
    m_nb_samples = stoi(line);

    std::getline(myfile, line);
    m_nb_features = stoi(line);

    while (getline(myfile, line))
    {
        m_data.push_back(new Sample(line));
    }

    myfile.close();
}

void Data::scale()
{
    // TODO : Function to define
}

int Data::getNbSamples()
{
    return m_nb_samples;
}

string Data::getString()
{
    string str = "";
    str += "Nombre de Sample : " + to_string(m_nb_samples) + "\n";
    str += "Nombre de Features/Sample : " + to_string(m_nb_features) + "\n";

    str += "Liste des samples : \n";
    for(const auto& value: m_data) {
        str += "\t" + value->getString() + "\n";
    }
    return str;
}
