#include "../inc/Data.h"

Data::Data()
{
    m_nb_features = 0;
    m_nb_samples = 0;
}

Data::Data(Data &d) {
    m_nb_features = d.m_nb_features;
    m_nb_samples = d.m_nb_samples;
    for(const auto& value: d.m_data) {
        m_data.push_back(new Sample(*value));
    }
}

Data::~Data()
{
    for (const auto &value: m_data) {
        delete value;
    }
}

void Data::add(Sample *s) {
    m_nb_samples +=1;
    m_data.push_back(s);
}

Data* Data::split(int percentage) {
    Data* n = new Data(*this);

    int nb_to_pop = m_nb_samples - (percentage * m_nb_samples / 100);
    m_data.erase(m_data.end()-(m_nb_samples-nb_to_pop), m_data.end());
    n->m_data.erase(n->m_data.begin(), n->m_data.begin()+nb_to_pop);

    m_nb_samples = nb_to_pop;
    n->m_nb_samples -= nb_to_pop;
    return n;
}

int Data::load_from_svm(std::string filepath)
{
    ifstream myfile(filepath); // open svm file

    if(!myfile)
    {
        cout << "File does not exist" << endl;
        return 0;
    }

    string line; // current line
    std::getline(myfile, line); // read first line
    m_nb_samples = stoi(line); // nb sample is first line

    std::getline(myfile, line); // read second line
    m_nb_features = stoi(line); // nb feature is second line

    while (getline(myfile, line)) {
        std::string temp_sval = ""; // temporary string value
        double temp_dval; // temporary double value
        std::vector<double> v; // temporary vector

        int t = stoi(&line.at(0)); // tag is first character
        line.erase(0, 2); // delete tag from line

        for (auto it = line.cbegin(); it != line.cend(); ++it) {
            // If character is different of simple space
            // Concatenate with previous
            if (*it != *" ") {
                temp_sval = temp_sval + *it;
            }
            // If last character or space
            // Convert into double and save at back of the vector
            if (*it == *" " or it == line.cend() - 1) {
                temp_dval = std::stod(temp_sval);
                v.push_back(temp_dval);
                temp_sval = "";
            }
        }

        FeatureVector *f = new FeatureVector(v); // Create FeatureVector
        m_data.push_back(new Sample(t, f)); // Create Sample
    }
    myfile.close(); // close file
    return 1;
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
    int i = 0;
    for (const auto &value: m_data) {
        i++;
        str += "\t Id = " + to_string(i) + "; " + value->getString() + "\n";
    }
    return str;
}
