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
 * Prototype function to scale two Data together
 *
 * @param Data Data object pointer to scale with self
 */
void Data::scale(Data *data) {
    double c, min, max;
    unsigned int size = data->getNbSamples();

    for (int i = 0; i < m_nb_features; i++) {
        //cout<< "i = " << i<<endl;

        min = (*m_data[0])[i];
        max = (*m_data[0])[i];

        for (const auto &sample: m_data) {
            c = (*sample)[i];
            if (c < min) min = c;
            if (c > max) max = c;
            //cout << "\tc = " << c << endl;
        }

        for (int j = 0; j < size; j++) {
            c = (*(*data)[j])[i];
            if (c < min) min = c;
            if (c > max) max = c;
            //cout << "\tc = " << c << endl;
        }
        //cout << "\tmin = " << min << endl;
        //cout << "\tmax = " << max << endl;


        for (const auto &sample: m_data) {
            c = ((*sample)[i] - min) / (max - min);
            //cout << "\tmodified c = " << c << endl;
            (*sample)[i] = c;
        }

        for (int j = 0; j < size; j++) {
            c = ((*(*data)[j])[i] - min) / (max - min);
            //cout << "\tmodified c = " << c << endl;
            (*(*data)[j])[i] = c;
            //cout << "\tc = " << c << endl;
        }

    }

    /*
    // print content
    int i = 0;
    for (const auto &sample: m_data) {
        cout << "sample : " << i << endl;
        for (int j = 0; j<m_nb_features; j++) {
            cout << (*(sample->getFeature()))[j] << endl;
        }
        i++;
    }
     */

    for (const auto &sample: m_data) {
        sample->getFeature()->norme();
    }

    for (int j = 0; j < size; j++) {
        (*(*data)[j]).getFeature()->norme();
    }
}

/**
 * Prototype function to scale Data between 0 and 1
 */
void Data::scale() {
    double c, min, max;
    for (int i = 0; i < m_nb_features; i++) {
        //cout<< "i = " << i<<endl;

        min = (*m_data[0])[i];
        max = (*m_data[0])[i];

        for (const auto &sample: m_data) {
            c = (*sample)[i];
            if (c < min) min = c;
            if (c > max) max = c;
            //cout << "\tc = " << c << endl;
        }
        //cout << "\tmin = " << min << endl;
        //cout << "\tmax = " << max << endl;


        for (const auto &sample: m_data) {
            c = ((*sample)[i] - min) / (max - min);
            //cout << "\tmodified c = " << c << endl;
            (*sample)[i] = c;
        }

    }

    /*
    // print content
    int i = 0;
    for (const auto &sample: m_data) {
        cout << "sample : " << i << endl;
        for (int j = 0; j<m_nb_features; j++) {
            cout << (*(sample->getFeature()))[j] << endl;
        }
        i++;
    }
     */

    for (const auto &sample: m_data) {
        sample->getFeature()->norme();
    }
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
