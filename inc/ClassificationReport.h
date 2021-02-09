#ifndef CLASSIFICATIONREPORT_H
#define CLASSIFICATIONREPORT_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class ClassificationReport {
public:
    ClassificationReport(vector<unsigned int> realTags, vector<unsigned int> guessedTags);
    string getString() const;

private:
    unsigned int m_ok = 0;
    unsigned int m_nok = 0;
    unsigned int m_nbTags = 0;
    unsigned int m_confusion[10][10]{};
};

#endif