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
        if(command.substr(0, 3) == "knn")
        {
            if(knn(command))
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

bool Command::knn(std::string command)
{
    // Initialisation of variable
    m_cosinus = false;
    m_distance = false;
    m_information = false;
    m_testDataPathValue = false;

    char c;
    bool endArg = false;
    int index = 3;

    // Verify space and declaration of argument
    if(command.substr(index, 2) != " -")
    {
        cout << "The arguments are missing" << endl;
        return false;
    }
    index += 2;

    // Verify first argument
    c = *command.substr(index, 1).c_str();
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
    index++;

    // Verify if second argument
    c = *command.substr(index, 1).c_str();
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
    }
    else
    {
        cout << "The second argument is wrong" << endl;
        return false;
    }
    index++;

    // Verify if third argument
    if(endArg == false)
    {
        c = *command.substr(index, 1).c_str();
        if(c == 'i')
        {
            m_information = true;
        }
        else if(c == ' ')
        {
            endArg = true;
        }
        else
        {
            cout << "The third argument is wrong" << endl;
            return false;
        }
        index++;
    }
    
    // Verify end of arguments
    if(endArg == false)
    {
        if(*command.substr(index, 1).c_str() != ' ')
        {
            cout << "Too many arguments" << endl;
            return false;
        }

        endArg = true;
        index++;
    }

    // Verify start of path
    if(endArg && *command.substr(index, 1).c_str() != '\"')
    {
        cout << "First path must start with: \"" << endl;
        return false;
    }

    // Find end of training data path
    size_t endPath = command.find(".svm\" \"", index);

    // Verify endPath
    if(endPath == string::npos)
    {
        cout << "First path must end with: .svm\" \"" << endl;
        return false;
    }

    // Save training data path
    m_trainingDataPath = command.substr(index + 1, endPath - index + 3);

    // Update index
    index = endPath + 7;

    // Find end of test data path
    endPath = command.find(".svm\" ", index);

    // Verify endPath
    if(endPath == string::npos)
    {
        cout << "Second path must end with: .svm\" " << endl;
        return false;
    }

    // Save test data path
    m_testDataPath = command.substr(index, endPath - index);

    // Verify if path or value
    if(m_testDataPath > "0" && m_testDataPath < "100")
    {
        m_testDataPathValue = true;
    }
    else
    {
        m_testDataPath = command.substr(index, endPath - index + 4);
    }

    // Update index
    index = endPath + 6;

    // Save k
    string k = command.substr(index, command.length() - index);

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
    cout << "help   Display information about commands" << endl;
    cout << endl;
    cout << "knn    Calculation of k nearest neighbors algorithm" << endl;
    cout << " Format:" << endl;
    cout << "    knn -[argument(s)] \"[training data path]\" \"[test data path]\" [k]" << endl;
    cout << " Mandatory argument(s):" << endl;
    cout << "  - c           Calculation with cosine similarity" << endl;
    cout << "  - d           Calculation with distance" << endl;
    cout << "  - cd          Calculation with both methods" << endl;
    cout << "  - dc          Calculation with both methods" << endl;
    cout << " Optional argument:" << endl;
    cout << "  - [arg(s)]i   Display information about results" << endl;
    cout << endl;
    cout << "exit   Exit the application" << endl << endl;
}
