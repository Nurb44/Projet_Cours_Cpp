#include "..\inc\Command.h"

//classifier -c "C:\a.svm" "C:\b.svm" 1

using namespace std;

Command::Command()
{
    cout << "WELCOME TO THE CLASSIFIER" << endl;
    cout << "If you need help, enter \"help\"" << endl;
}

Command::~Command()
{}

bool Command::process()
{
    // Declaration and initialisation of variables
    bool status = true;
    string command;

    // Wait user write command
    while(status)
    {
        // Read input
        cout << ">>";
        getline(cin, command);

        // Verify command
        if(command.substr(0, 11) == "classifier ") // Problem if end of string
        {
            if(classifier(command))
            {
                return status;
            }
        }
        else if(command.substr(0, 4) == "exit")
        {
            status = false;
        }
        else if(command.substr(0, 4) == "help")
        {
            help();
        }
    }
    return status;
}

bool Command::classifier(std::string command)
{
    // Initialisation of variable
    m_cosinus = false;
    m_distance = false;
    m_information = false;

    char c;
    bool endArg = false;
    int startPath = 0;

    // Verify declaration of argument
    if(command.at(11) == '-')
    {
        // Verify first argument
        c = command.at(12);
        if(c == 'c')
        {
            m_cosinus = true;
        }
        else if(c == 'd')
        {
            m_distance = true;
        }
        else
        {
            cout << "The first argument is wrong" << endl;
            return false;
        }

        // Verify if second argument
        c = command.at(13);
        if(m_distance && c == 'c')
        {
            m_cosinus = true;
        }
        else if(m_cosinus && c == 'd')
        {
            m_distance = true;
        }
        else if(c == 'i')
        {
            m_information = true;
        }
        else if(c == ' ')
        {
            endArg = true;
            startPath = 14;
        }
        else
        {
            cout << "The second argument is wrong" << endl;
            return false;
        }

        // Verify if third argument
        if(endArg == false)
        {
            c = command.at(14);
            if(c == 'i')
            {
                m_information = true;
            }
            else if(c == ' ')
            {
                endArg = true;
                startPath = 15;
            }
            else
            {
                cout << "The third argument is wrong" << endl;
                return false;
            }
        }
        
        // Verify end of arguments
        if(endArg == false)
        {
            if(command.at(15) == ' ')
            {
                endArg = true;
                startPath = 16;
            }
            else
            {
                cout << "Too many arguments" << endl;
                return false;
            }
        }

        // Verify start of path
        if(endArg && command.at(startPath) == '\"')
        {
            // Find end of training data path
            size_t endPath = command.find(".svm\" \"", startPath);
            // Verify endPath
            if(endPath == string::npos)
            {
                cout << "First path must end with: .svm\" \"" << endl;
                return false;
            }
            // Save training data path
            m_trainingDataPath = command.substr(startPath + 1, endPath - startPath + 3);
            // Update startPath
            startPath = endPath + 7;
            // Find end of test data path
            endPath = command.find(".svm\" ", startPath);
            // Verify endPath
            if(endPath == string::npos)
            {
                cout << "Second path must end with: .svm\" " << endl;
                return false;
            }
            // Save test data path
            m_testDataPath = command.substr(startPath, endPath - startPath + 4);
            // Update startPath
            startPath = endPath + 6;
            // Save k
            // TO DO (k < ?) penser à vérifier que k < nb sample dans training data
        }
        else
        {
            cout << "First path must start with: \"" << endl;
            return false;
        }
        return true;
    }
    else
    {
        cout << "The arguments are missing" << endl;
        return false;
    }
    return false;
}

void Command::help()
{
    cout << "help         Display information about commands" << endl;
    cout << endl;
    cout << "classifier   Calculation of k nearest neighbors algorithm" << endl;
    cout << " Format:" << endl;
    cout << "    classifier -[argument(s)] \"[training data path]\" \"[test data path]\" [k]" << endl;
    cout << " Mandatory argument(s):" << endl;
    cout << "  - c           Calculation with cosine similarity" << endl;
    cout << "  - d           Calculation with distance" << endl;
    cout << "  - cd          Calculation with both methods" << endl;
    cout << "  - dc          Calculation with both methods" << endl;
    cout << " Optional argument:" << endl;
    cout << "  - [arg(s)]i   Display information about results" << endl;
    cout << endl;
    cout << "exit         Exit the application" << endl << endl;
}
