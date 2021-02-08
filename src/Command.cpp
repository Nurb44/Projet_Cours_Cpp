#include "..\inc\Command.h"

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
    unsigned int error = 0;

    // Wait user write command
    while(status)
    {
        // Read input
        cout << ">>";
        getline(cin, command);

        // Verify command
        if(command.substr(0, 10) == "classifier")
        {
            if(classifier(command))
            {
                return status;
            }
            error++;
            if(error == 3)
            {
                cout << "If you need help, enter \"help\"" << endl;
                error = 0;
            }
        }
        else if(command.substr(0, 4) == "exit")
        {
            status = false;
        }
        else if(command.substr(0, 4) == "help")
        {
            help();
            error = 0;
        }
        else if(command == "\0")
        {}
        else
        {
            cout << "Command was not found" << endl;
            error++;
            if(error == 3)
            {
                cout << "If you need help, enter \"help\"" << endl;
                error = 0;
            }
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
    m_testDataPathValue = false;

    char c;
    bool endArg = false;
    int startPath = 0;

    // Verify space and declaration of argument
    if(command.substr(10, 2) != " -")
    {
        cout << "The arguments are missing" << endl;
        return false;
    }
    // Verify first argument
    c = *command.substr(12, 1).c_str();
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
    c = *command.substr(13, 1).c_str();
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
        c = *command.substr(14, 1).c_str();
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
        if(*command.substr(15, 1).c_str() != ' ')
        {
            cout << "Too many arguments" << endl;
            return false;
        }

        endArg = true;
        startPath = 16;
    }

    // Verify start of path
    if(endArg && *command.substr(startPath, 1).c_str() != '\"')
    {
        cout << "First path must start with: \"" << endl;
        return false;
    }

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
    m_testDataPath = command.substr(startPath, endPath - startPath);

    // Verify if path or value
    if(m_testDataPath > "0" && m_testDataPath < "100")
    {
        m_testDataPathValue = true;
    }
    else
    {
        m_testDataPath = command.substr(startPath, endPath - startPath + 4);
    }

    // Update startPath
    startPath = endPath + 6;

    // Save k
    string k = command.substr(startPath, command.length() - startPath);

    // Verify k
    if(k < "1" || k > "65535")
    {
        cout << "k must be between 1 and 65535" << endl;
        return false;
    }

    // Save k
    m_k = stoi(k);

    return true;
}

bool Command::getCosinus() const
{
    return m_cosinus;
}

bool Command::getDistance() const
{
    return m_distance;
}

bool Command::getInformation() const
{
    return m_information;
}

string Command::getTrainingDataPath() const
{
    return m_trainingDataPath;
}

string Command::getTestDataPath() const
{
    return m_testDataPath;
}

bool Command::getTestDataPathValue() const
{
    return m_testDataPathValue;
}

unsigned int Command::getK() const
{
    return m_k;
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
