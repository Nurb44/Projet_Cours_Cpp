#include "../inc/Knn.h"

Knn::Knn()
{}

unsigned int Knn::predict(Data d, FeatureVector *f, const unsigned int k, bool info)
{
    // Calculation of similarity
    std::vector<double> val = similarity(d, f);

    // k associated tag
    unsigned int *tag = predictSingle(k, val, d);
    if(info)
    {
        for(unsigned int i = 0; i < k; i++)
        {
            cout << i+1 << "knn's tag: " << tag[i] << endl;
        }
    }

    // Choose tag
    unsigned int nbTag[10];
    for(unsigned int i = 0; i < 10; i++)
    {
        nbTag[i] = 0;
    }
    for(unsigned int i = 0; i < k; i++)
    {
        nbTag[*tag++]++;
    }

    unsigned int tagMax = 0;
    unsigned int nbTagTmp = nbTag[0];
    for(unsigned int i = 0; i < 9; i++)
    {
        if(nbTagTmp < nbTag[i + 1])
        {
            nbTagTmp = nbTag[i + 1];
            tagMax = i + 1;
        }
    }

    return tagMax;
}
