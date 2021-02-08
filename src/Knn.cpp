#include "../inc/Knn.h"

Knn::Knn()
{}

int Knn::predict(Data d, FeatureVector *f, const unsigned int k)
{
    // Calculation of cosinus similarity
    std::vector<double> cos = similarity(d, f);

    // k associated tag
    int *tag = predictSingle(k, cos, d);

    // Choose tag
    unsigned int nbTag[10];
    for(unsigned int i = 0; i < k; i++)
    {
        nbTag[tag[i]]++;
    }
    int tagMax = 0;
    for(unsigned int i = 0; i < k - 1; i++)
    {
        if(nbTag[i] < nbTag[i + 1])
        {
            tagMax = i + 1;
        }
    }

    return tagMax;
}
