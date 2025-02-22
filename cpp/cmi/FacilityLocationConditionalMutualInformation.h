#ifndef FLCMI_H
#define FLCMI_H
#include "../condgain/ConditionalGain.h"
#include "../smi/MutualInformation.h"
#include "../submod/FacilityLocation.h"

class FacilityLocationConditionalMutualInformation : public SetFunction {
   protected:
    ll n;
    int numPrivates;
    int numQueries;
    float magnificationLambda;
    float privacyHardness;
    std::unordered_set<ll> indexCorrectedP;
    std::unordered_set<ll> indexCorrectedQ;
    std::vector<std::vector<float>> kernelImage;       // n X n
    std::vector<std::vector<float>> kernelPrivate;       // n X numPrivates
    std::vector<std::vector <float> > kernelQuery;   //n X numQueries
    std::vector<std::vector<float>> superKernel;       
    FacilityLocation *facLoc;
    ConditionalGain *condGain;
    MutualInformation *mutualInfo;

   public:
    FacilityLocationConditionalMutualInformation(
        ll n_, int numQueries_, int numPrivates_,
        std::vector<std::vector<float>> const &kernelImage_,
        std::vector<std::vector<float>> const &kernelQuery_,
        std::vector<std::vector<float>> const &kernelPrivate_,
        float magnificationLambda_,
        float privacyHardness_);

    double evaluate(std::unordered_set<ll> const &X);
    double evaluateWithMemoization(std::unordered_set<ll> const &X);
    double marginalGain(std::unordered_set<ll> const &X, ll item);
    double marginalGainWithMemoization(std::unordered_set<ll> const &X,
                                       ll item, bool enableChecks=true);
    void updateMemoization(std::unordered_set<ll> const &X, ll item);
    std::unordered_set<ll> getEffectiveGroundSet();
    // std::vector<std::pair<ll, double>> maximize(std::string, ll budget,
    //                                             bool stopIfZeroGain,
    //                                             bool stopIfNegativeGain,
    //                                             float epsilon, bool verbose, bool showProgress);
    void clearMemoization();
    void setMemoization(std::unordered_set<ll> const &X);
    // FacilityLocationConditionalMutualInformation* clone();
};
#endif