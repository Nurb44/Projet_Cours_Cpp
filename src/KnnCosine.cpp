#include "../inc/KnnCosine.h"

/**
 * Constructor KnnCosine
 */
KnnCosine::KnnCosine(): Knn()
{}

/**
 * Prediction of knn
 * 
 * @param k number of knn
 * @param cos vector of cosine simularity
 * @param d training data
 * @return tag array of knn
 */
unsigned int* KnnCosine::predictSingle(const unsigned int k, std::vector<double> cos, Data d)
{
    // Declaration & initialisation of kppv and tag array
    double kppv[k];
    for(unsigned int i = 0; i < k; i++)
    {
        kppv[i] = -1;
    }
    unsigned int *tag = new unsigned int[k];

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

/**
 * Calculation of cosine simularity
 * 
 * @param d training data
 * @param f feacture vector to test
 * @return vector of cosine simularity
 */
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
