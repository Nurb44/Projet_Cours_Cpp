#include "../inc/Data.h"

Data::Data()
{
    m_nb_features = 0;
    m_nb_samples = 0;
}

Data::~Data()
{
    for (const auto &value: m_data) {
        delete value;
    }
}

void Data::load_from_svm(std::string filepath)
{
    ifstream myfile(filepath); // open svm file

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

        FeatureVector *f = new FeatureVector(&v); // Create FeatureVector
        m_data.push_back(new Sample(t, f)); // Create Sample
    }
    myfile.close(); // close file
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
