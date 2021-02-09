#include <iostream>
#include <stdlib.h>
#include <vector>
#include "..\inc\Command.h"
#include "..\inc\Timer.h"
#include "..\inc\Data.h"
#include "..\inc\KnnCosine.h"
#include "..\inc\ClassificationReport.h"

using namespace std;

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
        Data *testData = new Data();
        // Load for training data
        if(trainingData.load_from_svm(cmd.getTrainingDataPath()))
        {
            // If value then split for test data
            if(cmd.getTestDataPathStatus())
            {
                delete testData;
                testData = trainingData.split(cmd.getTestDataPathValue());
                process = true;
            }
            // If path then load for test data
            else
            {
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
                    // Declaration of variables for classification report
                    vector<unsigned int> tag;
                    vector<unsigned int> predictTagCos;
                    vector<unsigned int> predictTagDist;
                    // Test all samples of test data
                    for(unsigned int i = 0; i < testData->getNbSamples(); i++)
                    {
                        // Declaration of predict tag
                        unsigned int predictTag;
                        // Cosine calculation
                        if(cmd.getCosinus())
                        {
                            KnnCosine knnCos = KnnCosine();
                            predictTag = knnCos.predict(trainingData, (*testData)[i]->getFeature(), cmd.getK(), cmd.getInformation());
                            tag.push_back((*testData)[i]->getTag());
                            predictTagCos.push_back(predictTag);
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

                    // Classification report
                    if(cmd.getCosinus())
                    {
                        ClassificationReport reportCos(tag, predictTagCos);
                        cout << reportCos.getString() << endl;
                    }
                    if(cmd.getDistance())
                    {
                        ClassificationReport reportDist(tag, predictTagDist);
                        cout << reportDist.getString() << endl;
                    }

                    // Stop and display timer
                    cout << tmr.getString() << endl;
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
