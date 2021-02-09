#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "..\inc\Command.h"
#include "..\inc\Data.h"
#include "..\inc\KnnCosine.h"
#include "..\inc\ClassificationReport.h"

using namespace std;

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

int main()
{
    // Enter command line
    Command cmd = Command();

    while(cmd.process())
    {
        // Start timer
        Timer tmr;

        // Process
        bool process = false;
        // Declaration of data
        Data trainingData;
        Data *testData;
        // Load for training data
        if(trainingData.load_from_svm(cmd.getTrainingDataPath()))
        {
            // If value then split for test data
            if(cmd.getTestDataPathValue())
            {
                testData = trainingData.split(stoi(cmd.getTestDataPath()));
                process = true;
                cout << testData->getString() << endl;
            }
            // If path then load for test data
            else
            {
                testData = new Data();
                if(testData->load_from_svm(cmd.getTestDataPath()))
                {
                    process = true;
                }
            }
            // Verify process
            if(process)
            {
                // Verify k <= nb sample
                if(cmd.getK() <= trainingData.getNbSamples())
                {
                    // Test all samples of test data
                    for(unsigned int i = 0; i < testData->getNbSamples(); i++)
                    {
                        // Declaration of predict tag
                        int predictTag;
                        // Cosine calculation
                        if(cmd.getCosinus())
                        {
                            KnnCosine knnCos = KnnCosine();
                            predictTag = knnCos.predict(trainingData, (*testData)[i]->getFeature(), cmd.getK(), cmd.getInformation());
                            if(cmd.getInformation())
                            {
                                cout << predictTag << " == " << (*testData)[i]->getTag() << " ? " << (predictTag == (*testData)[i]->getTag()) << endl;
                            }
                        }
                        // Distance calculation
                        if(cmd.getDistance())
                        {
                            
                        }
                    }

                    // Stop and display timer
                    double t = tmr.elapsed();
                    cout << "Time to work: " << t << endl;
                }
                else
                {
                    cout << "k must be less than the number of samples" << endl;
                }
            }
        }
    }
    return 0;
}
