#include "../inc/KnnCosine.h"

KnnCosine::KnnCosine(): Knn()
{}

int* KnnCosine::predictSingle(const unsigned int k, std::vector<double> cos, Data d)
{
    // Declaation & initialisation of kppv and tag array
    double kppv[k];
    for(unsigned int i = 0; i < k; i++)
    {
        kppv[i] = -1;
    }
    int *tag = new int[k];

    // Sort cosinus similarity and associated tag
    for(unsigned int i = 0; i < cos.size(); i++)
    {
        for(unsigned int j = 0; j < k; j++)
        {
            if(kppv[j] < cos[i])
            {
                for(unsigned int m = 1; m < k - j; m++)
                {
                    kppv[k - m] = kppv[k - m - 1];
                    tag[k - m] = tag[k - m - 1];
                }
                kppv[j] = cos[i];
                tag[j] = d[i]->getTag();
                j = k;
            }
        }
    }

    return tag;
}

std::vector<double> KnnCosine::similarity(Data d, FeatureVector *f)
{
    // Declaration of cosinus similarity vector
    std::vector<double> cos;

    // Calculation of cosinus similarity
    for(unsigned int i = 0; i < d.getNbSamples(); i++)
    {
        cos.push_back((*d[i]->getFeature() * f) / (d[i]->getFeature()->getNorme() * f->getNorme()));
    }

    return cos;
}
