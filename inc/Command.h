#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>

class Command
{
    public:
    Command();
    ~Command();
    bool process();
    bool getCosinus() const;
    bool getDistance() const;
    bool getInformation() const;
    std::string getTrainingDataPath() const;
    std::string getTestDataPath() const;
    bool getTestDataPathValue() const;
    unsigned int getK() const;
    
    private:
    bool knn(std::string command);
    void help();

    bool m_cosinus;
    bool m_distance;
    bool m_information;
    std::string m_trainingDataPath;
    std::string m_testDataPath;
    bool m_testDataPathValue;
    unsigned int m_k;
};

#endif