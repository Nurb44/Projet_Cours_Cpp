#include "../inc/ClassificationReport.h"

/**
 * Constructor ClassificationReport.
 *
 * @param realTags Vector of known tags.
 * @param guessedTags Vector of guessed tags.
 */
ClassificationReport::ClassificationReport(vector<unsigned int> realTags, vector<unsigned int> guessedTags) {
    for (int i = 0; i < realTags.size(); i++) {
        m_nbTags++;
        m_confusion[realTags[i]][guessedTags[i]]++;
        if (realTags[i] == guessedTags[i])
            m_ok++;
        else
            m_nok++;
    }
}

/**
 * Give string representation of the ClassificationReport.
 *
 * @return String representation of the ClassificationReport.
 */
string ClassificationReport::getString() const {
    std::stringstream fok;
    std::stringstream fnok;
    fok << std::fixed << std::setprecision(2) << float(m_ok) * 100 / float(m_nbTags);
    fnok << std::fixed << std::setprecision(2) << float(m_nok) * 100 / float(m_nbTags);

    string str = "In " + to_string(m_nbTags) + " tests, " + \
    to_string(m_ok) + " results are correct(" + fok.str() + "%), " + \
    "while " + to_string(m_nok) + " are incorrect(" + fnok.str() + "%).\n";

    str += "Here is confusion matrix (R:Real/G:Guessed) :\n";
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