#include "../inc/ClassificationReport.h"

ClassificationReport::ClassificationReport(vector<unsigned int> realData, vector<unsigned int> guessedData) {
    for (int i = 0; i < realData.size(); i++) {
        m_nbTags++;
        m_confusion[realData[i]][guessedData[i]]++;
        if (realData[i] == guessedData[i])
            m_ok++;
        else
            m_nok++;
    }
}

string ClassificationReport::getString() const {
    std::stringstream fok;
    std::stringstream fnok;
    fok << std::fixed << std::setprecision(2) << float(m_ok) * 100 / m_nbTags;
    fnok << std::fixed << std::setprecision(2) << float(m_nok) * 100 / m_nbTags;

    string str = "Sur " + to_string(m_nbTags) + " tests, " + \
    to_string(m_ok) + " resultats sont corrects(" + fok.str() + "%), " + \
    "alors que " + to_string(m_nok) + " sont faux(" + fnok.str() + "%).\n";

    str += "Voici la matrice de confusion (R:Real/G:Guessed) :\n";
    str += "R/G\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n";
    int j, i;
    for (j = 0; j < 10; j++) {
        string line = to_string(j) + " |";
        for (i = 0; i < 10; i++) {
            line += "\t" + to_string(m_confusion[j][i]);
        }
        str += line + "\n";
    }
    return str;
}
