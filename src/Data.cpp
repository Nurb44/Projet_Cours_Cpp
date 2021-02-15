#include "../inc/Data.h"

/**
 * Constructor Data.
 */
Data::Data() {
    m_nb_features = 0;
    m_nb_samples = 0;
}

/**
 * Copy constructor Data.
 *
 * @param d Reference to a Data.
 */
Data::Data(Data &d) {
    m_nb_features = d.m_nb_features;
    m_nb_samples = d.m_nb_samples;
    for (const auto &value: d.m_data) {
        m_data.push_back(new Sample(*value));
    }
}

/**
 * Destructor Data.
 */
Data::~Data() {
    for (const auto &value: m_data) {
        delete value;
    }
}

/**
 * Shuffle m_data
 */
void Data::shuffle() {
    srand(time(0));
    random_shuffle(begin(m_data), end(m_data));
}

/**
 * Split Data using ratio.
 * Remove part from obj1 to put it into obj2
 *
 * @param ratio Ratio to split between obj1 and obj2.
 * @return New Data pointer.
 */
Data *Data::split(unsigned int ratio) {
    if (ratio < 1 || ratio > 99)
        return nullptr;

    Data *n = new Data(*this);

    unsigned int nb_to_pop = m_nb_samples - (ratio * m_nb_samples / 100);
    m_data.erase(m_data.end() - (m_nb_samples - nb_to_pop), m_data.end());
    n->m_data.erase(n->m_data.begin(), n->m_data.begin() + nb_to_pop);

    m_nb_samples = nb_to_pop;
    n->m_nb_samples -= nb_to_pop;
    return n;
}

/**
 * Open SVM file and load data
 *
 * @param filepath SVM file to read from.
 * @return True if succeeded, False else.
 */
bool Data::load_from_svm(const std::string &filepath) {
    ifstream file(filepath); // open svm file

    if (!file) {
        cout << "File does not exist" << endl;
        return false;
    }

    string line; // current line
    std::getline(file, line); // read first line
    m_nb_samples = stoi(line); // nb sample is first line

    std::getline(file, line); // read second line
    m_nb_features = stoi(line); // nb feature is second line

    while (getline(file, line)) {
        std::string temp_sval; // temporary string value
        double temp_dval; // temporary double value
        std::vector<double> v; // temporary vector

        int t = stoi(&line.at(0)); // tag is first character
        line.erase(0, 2); // delete tag from line

        for (auto it = line.cbegin(); it != line.cend(); ++it) {
            // If character is different of simple space
            // Concatenate with previous
            if (*it != *" ") {
                temp_sval += *it;
            }
            // If last character or space
            // Convert into double and save at back of the vector
            if (*it == *" " or it == line.cend() - 1) {
                temp_dval = std::stod(temp_sval);
                v.push_back(temp_dval);
                temp_sval = "";
            }
        }

        auto *f = new FeatureVector(v); // Create FeatureVector
        m_data.push_back(new Sample(t, f)); // Create Sample
    }
    file.close(); // close file
    return true;
}

/**
 * Accessor of m_nb_samples.
 *
 * @return number of samples in Data.
 */
unsigned int Data::getNbSamples() const {
    return m_nb_samples;
}

/**
 * Give string representation of the Data.
 *
 * @return String representation of the Data.
 */
string Data::getString() const {
    string str;
    str += "Number of Sample : " + to_string(m_nb_samples) + "\n";
    str += "Number of Feature by Sample : " + to_string(m_nb_features) + "\n";

    str += "Sample list : \n";
    int i = 0;
    for (const auto &value: m_data) {
        i++;
        str += "\t Id = " + to_string(i) + "; " + value->getString() + "\n";
    }
    return str;
}
