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
    
    private:
    bool classifier(std::string command);
    void help();

    bool m_cosinus;
    bool m_distance;
    bool m_information;
    std::string m_trainingDataPath;
    std::string m_testDataPath;
    unsigned int m_k;
};

#endif