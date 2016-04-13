
#include "TvSVM.h"

using namespace std;

TvSVM::TvSVM(void)
{
}


TvSVM::~TvSVM(void)
{
}


vector<float> TvSVM::get_linear_weight(void)
{
    CvSVMDecisionFunc *df;
    vector<float> weight;
    int varcount;
    float *svector;
    double alpha;

    varcount = get_var_count();
    df = decision_func;
    if (df)
    {
        weight.resize(varcount, 0);
        for (int i=0; i<sv_total; i++)
        {
            svector = (float *)get_support_vector(df->sv_index[i]);
//          alpha = df->alpha[i];
            alpha = -1.0 * df->alpha[i];
            for (int j=0; j<varcount; j++)
            {
                weight[j] += (float)((double)svector[j] * alpha);
            }
        }
    }

//    weight.push_back(-df->rho);
    weight.push_back((float)df->rho);
    printf("\nrho: %f\n", df->rho);

    return weight;
}
