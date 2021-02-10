#include "../inc/KnnDistance.h"

KnnDistance::KnnDistance(): Knn()
{}

unsigned int* KnnDistance::predictSingle(const unsigned int k, std::vector<double> dist, Data d)
{
    // Declaration & initialisation of kppv and tag array
    double kppv[k];
    for(unsigned int i = 0; i < k; i++)
    {
        kppv[i] = DBL_MAX;
    }
    unsigned int *tag = new unsigned int[k];

    // Sort distance and associated tag
    for(unsigned int i = 0; i < dist.size(); i++)
    {
        for(unsigned int j = 0; j < k; j++)
        {
            if(kppv[j] > dist[i])
            {
                for(unsigned int m = 1; m < k - j; m++)
                {
                    kppv[k - m] = kppv[k - m - 1];
                    tag[k - m] = tag[k - m - 1];
                }
                kppv[j] = dist[i];
                tag[j] = d[i]->getTag();
                j = k;
            }
        }
    }

    return tag;
}

std::vector<double> KnnDistance::similarity(Data d, FeatureVector *f)
{
    // Declaration of distance vector
    std::vector<double> dist;

    // Calculation of distance
    for(unsigned int i = 0; i < d.getNbSamples(); i++)
    {
        dist.push_back(0);
        for(unsigned int j = 0; j < f->getSize(); j++)
        {
            dist[i] += abs((*d[i]->getFeature())[j] - (*f)[j]);
        }
    }

    return dist;
}
