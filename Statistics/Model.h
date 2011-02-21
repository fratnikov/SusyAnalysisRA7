#ifndef MODEL_H
#define MODEL_H

#include<vector>
#include<string>
#include<sstream>
#include "RooFit.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooPoisson.h"
#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooArgSet.h"
#include"RooPolynomial.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "TMath.h"
#include "RooRandom.h"

class Model
{
  public:
    Model();
    //constructor reading input from config file
    Model(const char* config_file);
    //constructor reading input from vectors
    Model(std::vector<double>* signal_expectation,std::vector< std::vector<double>* >* background_expectation,std::vector< vector< vector<double>* >* >* systematic_uncertainties=0,std::vector<int>* n_input=0,int nuisance_range=10,int POI_range=20,int observation_range=20000);
    ~Model();
    
    
    //see, what the model looks like
    void Print();
       
    //get the parameter of interest
    RooRealVar* get_POI();
    //get a RooArgSet* containing the parameter of interest
    RooArgSet* get_POI_set();
    //get a RooArgSet* containing all nuisance parameters
    RooArgSet* get_nuisance_set();
    //get a RooArgSet* containing all observables
    RooArgSet* get_observable_set();
    //get a RooProdPdf* containing all s+b Poisson distributions multiplied
    RooProdPdf* get_sb_likelihood();
    //get a RooProdPdf* containing all b Poisson distributions multiplied
    RooProdPdf* get_b_likelihood();
    //get a RooProdPdf* containing all s+b poissons and the nuisance distributions
    RooProdPdf* get_complete_likelihood();
    //get a RooProdPdf* with all the nuisance distributions multiplied
    RooProdPdf* get_nuisance_prior_pdf();
    //get the prior pdf for the parameter of interest
    RooProdPdf* get_POI_prior();
    //get the data set
    RooDataSet* get_data();

    void set_dataset(RooDataSet* d);
    void set_nuisance_const();
    void set_nuisance_var();
    void set_poi_const(double p = 0);
    void set_poi_var(double p = 0);
    std::vector< RooConstVar*>* signal;
    std::vector< RooRealVar*>* observables;

    void test(string file);
  private:
    
    int n_channels;
    int n_backgrounds;
    int n_nuisances;
    bool use_nuisances;
    bool corrupted;
    
    int range_n_obs;
    int range_nuisances;
    int range_POI;
    
    RooRealVar* POI;
 
    std::vector< std::vector<RooConstVar*>* >* background;
    //std::vector< RooRealVar*>* observables;
    std::vector<string> *nuisance_names;
    std::vector<double> *nuisance_upper_limit;
    std::vector<RooRealVar*> *nuisance_parameters;
    std::vector<RooConstVar*> *nuisance_widths;
    std::vector<RooFormulaVar*> *nuisance_means;
    std::vector< std::vector< std::vector<RooConstVar*>* >* >* scaling_factors;
    std::vector<RooFormulaVar*> *sb_means;
    std::vector<RooFormulaVar*> *b_means;
    std::vector<RooPoisson*> *sb_poissons;
    std::vector<RooPoisson*> *b_poissons;

    
    
    RooArgSet* POI_set;
    RooArgSet* observable_set;
    RooArgSet* nuisance_set;
    
    std::vector<RooAbsPdf*> *nuisance_priors;
    RooProdPdf* nuisance_prior_pdf;    
    RooProdPdf* POI_prior_pdf;
    RooProdPdf* sb_likelihood;
    RooProdPdf* b_likelihood;
    RooDataSet* data;
    


    bool check_input(std::vector<int>* n_input,std::vector<double>* signal_expectation,std::vector< std::vector<double>* >* background_expectation,std::vector< std::vector< std::vector<double>* >* >* systematic_uncertainties);
    
    bool create_dataset(std::vector<int>* n_input);    
    
    void create_observables();
    
    void create_signal_expectations(std::vector<double>* signal_expectation);
    
    void create_background_expectations(std::vector< std::vector<double>* >* background_expectation);
    
    void create_nuisances(std::vector< std::vector< std::vector<double>* >* >* systematic_uncertainties);
    
    void create_scaling_factors(std::vector< std::vector< std::vector<double>* >* >* systematic_uncertainties);
    
    void create_nuisance_priors();
  
    void create_nuisance_priors_2();
    
    void create_POI();
    
    void create_POI_prior();
    
    void create_sb_likelihood();
    
    void create_b_likelihood();   
    
    void set_random_seed(int i);

    

};

#endif
