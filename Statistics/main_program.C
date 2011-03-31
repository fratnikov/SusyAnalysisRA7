#include <vector>
#include"RooPlot.h"
#include"TCanvas.h"
#include"TFile.h"
#include "RooStats/BayesianCalculator.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "Model.h"
#include "Hybrid_method.h"
#include "RooStats/HybridCalculatorOriginal.h"
#include "RooStats/HybridResult.h"
#include "RooStats/HybridPlot.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/FeldmanCousins.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/PointSetInterval.h"
#include "RooStats/ConfidenceBelt.h"
#include "RooWorkspace.h"

#include "RooStats/MCMCCalculator.h"
#include "RooStats/MCMCInterval.h"
#include "RooStats/MCMCIntervalPlot.h"



#include "BAT/BATCalculator.h"
#include <fstream>
#include <sstream>




using namespace std;
using namespace RooFit;
using namespace RooStats;

void fill_with_zeros(vector<double> &v,int n_entries){
  for(int i=0;i<n_entries;i++){
   v.push_back(0); 
  }
}


void central_interval_Profile_Likelihood(Model* model,double confidence){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating central confidence interval with the Profile Likelihood method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  
  //      //define paramsOfInterest
     RooArgSet *paramsOfInterest=new RooArgSet("paramsOfInterest");
     paramsOfInterest->addClone(*model->get_POI()); 	//clone because we need s for complete likelihood
     
     //get the calculator
     ProfileLikelihoodCalculator plc(*model->get_data(),*model->get_complete_likelihood(), *paramsOfInterest);
     
     //      //get the confidence interval
     LikelihoodInterval* lrint = (LikelihoodInterval*) plc.GetInterval();
     lrint->SetConfidenceLevel(confidence);
     double ll=lrint->LowerLimit(*model->get_POI());
     double ul=lrint->UpperLimit(*model->get_POI());
     cout<<confidence<<"% inter val is "<<ll<<" , "<<ul<<endl;

}

// void upper_limit_Profile_Likelihood(Model* model,double confidence){
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
//   cout<<"Calculating upper limit with the Profile Likelihood method"<<endl;
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  
//   //      //define paramsOfInterest
//      RooArgSet *paramsOfInterest=new RooArgSet("paramsOfInterest");
//      paramsOfInterest->addClone(*model->get_POI()); 	//clone because we need s for complete likelihood
     
//      //get the calculator
//      ProfileLikelihoodCalculator plc(*model->get_data(),*model->get_complete_likelihood(), *paramsOfInterest);
     
//      //      //get the confidence interval
//      LikelihoodInterval* lrint = (LikelihoodInterval*) plc.GetInterval();
//      lrint->SetConfidenceLevel(1-(1-confidence)*2);
//      double ul=lrint->UpperLimit(*model->get_POI());
//      cout<<confidence<<"% upper limit is "<<ul<<endl;
//      TCanvas *c1=new TCanvas;
//      LikelihoodIntervalPlot* lrplot1 = new LikelihoodIntervalPlot(lrint);
//      lrplot1->Draw(); 
//      c1->SaveAs("pll_plot.png");
     

// }

double upper_limit_Profile_Likelihood(Model* model,double confidence){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Profile Likelihood method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  
  //      //define paramsOfInterest
     RooArgSet *paramsOfInterest=new RooArgSet("paramsOfInterest");
     paramsOfInterest->addClone(*model->get_POI()); 	//clone because we need s for complete likelihood
     
     //get the calculator
     ProfileLikelihoodCalculator plc(*model->get_data(),*model->get_complete_likelihood(), *paramsOfInterest);
     
     //      //get the confidence interval
     LikelihoodInterval* lrint = (LikelihoodInterval*) plc.GetInterval();
     lrint->SetConfidenceLevel(1-(1-confidence)*2);
     double ul=lrint->UpperLimit(*model->get_POI());
     cout<<confidence<<"% upper limit is "<<ul<<endl;
  //    TCanvas *c1=new TCanvas;
//      LikelihoodIntervalPlot* lrplot1 = new LikelihoodIntervalPlot(lrint);
//      lrplot1->Draw(); 
//      c1->SaveAs("pll_plot6.png");
     
     
     return ul;
}




void significance_Profile_Likelihood(Model* model){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating significance with the Profile Likelihood method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  
  //      //define paramsOfInterest
     RooArgSet *paramsOfInterest=new RooArgSet("paramsOfInterest");
     paramsOfInterest->addClone(*model->get_POI()); 	//clone because we need s for complete likelihood
     
     //get the calculator
     ProfileLikelihoodCalculator plc(*model->get_data(),*model->get_complete_likelihood(), *paramsOfInterest);

     //define null hypothesis
     paramsOfInterest->setRealValue(model->get_POI()->GetName(),0);
     plc.SetNullParameters(*paramsOfInterest);
     
     //get the hypotest
     HypoTestResult* lrhypo=plc.GetHypoTest();
     double significance=lrhypo->Significance();     
     cout<<"Profile Likelihood significance is: "<<significance<<endl;
}

void upper_limit_Bayesian(Model* model,double confidence){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Bayesian method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  RooWorkspace* wspace = new RooWorkspace("wspace");
  ModelConfig* modelConfig = new ModelConfig("bayes");
  modelConfig->SetWorkspace(*wspace);
  modelConfig->SetPdf(*model->get_complete_likelihood());
  modelConfig->SetPriorPdf(*model->get_POI_prior());
  modelConfig->SetParametersOfInterest(*model->get_POI_set());
  //modelConfig->SetNuisanceParameters(*model->get_nuisance_set());



  //configure the calculator
  //model->Print();

  cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 
  BayesianCalculator bcalc(*model->get_data(), *modelConfig);
  //BayesianCalculator bcalc(*model->get_data(),*model->get_complete_likelihood(),*model->get_POI_set(),*model->get_POI_prior(),model->get_nuisance_set());
  //BayesianCalculator bcalc(*model->get_data(),*model->get_complete_likelihood(),*model->get_POI_set(),*model->get_POI_prior(),0);
 

  bcalc.SetLeftSideTailFraction(0); //for upper limit

  //get the interval
  bcalc.SetConfidenceLevel(confidence);
  cout<<"Calculating"<<endl;
  SimpleInterval* interval = bcalc.GetInterval();
  double ul=interval->UpperLimit();
  std::cout <<confidence <<"% CL upper limit: "<< ul<<endl;

  TCanvas *c1=new TCanvas;
  bcalc.SetScanOfPosterior(100);
  RooPlot * plot = bcalc.GetPosteriorPlot();
  plot->Draw(); 
  c1->SaveAs("bayesian_PosteriorPlot.png");

}

// void upper_limit_Bayesian_BAT(Model* model,double confidence,int Niters){
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
//   cout<<"Calculating upper limit with the Bayesian method(BAT)"<<endl;
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
//   RooWorkspace* wspace = new RooWorkspace("wspace");
//   RooStats::ModelConfig* modelConfig = new ModelConfig("bayes");
//   modelConfig->SetWorkspace(*wspace);
//   modelConfig->SetPdf(*model->get_complete_likelihood());
//   modelConfig->SetPriorPdf(*model->get_POI_prior());
//   modelConfig->SetParametersOfInterest(*model->get_POI_set());
//   modelConfig->SetNuisanceParameters(*model->get_nuisance_set());


//   cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 
 


//   //BATCalculator batcalc(model->get_data(), model->get_complete_likelihood(), model->get_POI_set(), model->get_POI_prior());
//   BATCalculator batcalc(*model->get_data(), *modelConfig);
//   batcalc.SetConfidenceLevel(1-(2*(1-confidence)));
//   batcalc.SetnMCMC(Niters);
//   //batcalc.SetNbins("POI",100);
//   cout<<confidence<<"% CL upper limit: " <<batcalc.GetInterval()->UpperLimit()<<endl;

//   double prec=batcalc.GetBrfPrecision();
 

// }

double upper_limit_Bayesian_BAT(Model* model,double confidence,int Niters){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Bayesian method(BAT)"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  RooWorkspace* wspace = new RooWorkspace("wspace");
  RooStats::ModelConfig* modelConfig = new ModelConfig("bayes");
  modelConfig->SetWorkspace(*wspace);
  modelConfig->SetPdf(*model->get_complete_likelihood());
  modelConfig->SetPriorPdf(*model->get_POI_prior());
  modelConfig->SetParametersOfInterest(*model->get_POI_set());
  modelConfig->SetNuisanceParameters(*model->get_nuisance_set());


  cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 
 


  //BATCalculator batcalc(model->get_data(), model->get_complete_likelihood(), model->get_POI_set(), model->get_POI_prior());
  BATCalculator batcalc(*model->get_data(), *modelConfig);
  batcalc.SetConfidenceLevel(1-(2*(1-confidence)));
  batcalc.SetnMCMC(Niters);
  //batcalc.SetNbins("POI",100);
  double ul=batcalc.GetInterval()->UpperLimit();
  cout<<confidence<<"% CL upper limit: " <<ul<<endl;

  //double prec=batcalc.GetBrfPrecision();
  return ul;

}


void upper_limit_Bayesian_MCMC(Model* model,double confidence,int Niters){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the MCMC method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  RooWorkspace* wspace = new RooWorkspace("wspace");
  ModelConfig* modelConfig = new ModelConfig("bayes");
  modelConfig->SetWorkspace(*wspace);
  modelConfig->SetPdf(*model->get_complete_likelihood());
  modelConfig->SetPriorPdf(*model->get_POI_prior());
  modelConfig->SetParametersOfInterest(*model->get_POI_set());
  //  modelConfig->SetNuisanceParameters();
  modelConfig->SetNuisanceParameters(*model->get_nuisance_set());


  //configure the calculator
  //model->Print();

  cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 
  RooRealVar* firstPOI = (RooRealVar*) modelConfig->GetParametersOfInterest()->first();


  MCMCCalculator mcmccalc(*model->get_data(), *modelConfig );
  mcmccalc.SetTestSize(1-confidence);
  mcmccalc.SetLeftSideTailFraction(0);
  mcmccalc.SetNumIters(Niters);
  MCMCInterval* interval = mcmccalc.GetInterval();
  double ul = interval->UpperLimit(*firstPOI);
  cout<<"UpperLimit: "<<ul<<endl;

}












// void upper_limit_FC(Model* model,double confidence){
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
//   cout<<"Calculating upper limit with the FC method"<<endl;
//   cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
//   RooWorkspace* wspace = new RooWorkspace("wspace");

//   ModelConfig* modelConfig = new ModelConfig("FC");
//   modelConfig->SetWorkspace(*wspace);
//   modelConfig->SetPdf(*model->get_complete_likelihood());
//   modelConfig->SetPriorPdf(*model->get_POI_prior());
//   modelConfig->SetParametersOfInterest(*model->get_POI_set());
//   //modelConfig->SetParametersOfInterest(*wspace->set("poi"));
//   //modelConfig->SetNuisanceParameters(*wspace->set("nuis"));
//   // modelConfig->SetNuisanceParameters();
//   modelConfig->SetNuisanceParameters(*model->get_nuisance_set());

//   RooDataSet* data = model->get_data();
//   RooArgSet* poi= model->get_POI_set();
//   //configure the calculator
//   //model->Print();



//   cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 

//   // use FeldmaCousins (takes ~20 min)  
//   FeldmanCousins fc(*data, *modelConfig);
//   fc.SetConfidenceLevel(0.95); //0.9 central limit=0.95 upper limit
//   //number counting: dataset always has 1 entry with N events observed
//   fc.FluctuateNumDataEntries(false); 
//   fc.UseAdaptiveSampling(true);
//   fc.SetNBins(80);
//   PointSetInterval* fcInt = NULL;
//   RooRealVar* firstPOI = (RooRealVar*) modelConfig->GetParametersOfInterest()->first();

//   //  if(doFeldmanCousins){ // takes 7 minutes
//     fcInt = (PointSetInterval*) fc.GetInterval(); // fix cast
//     //xs}

//     cout<<" ["<<fcInt->LowerLimit( *firstPOI ) << ", " <<
//     fcInt->UpperLimit( *firstPOI ) << "]" << endl;

 
// }


double upper_limit_FC(Model* model,double confidence){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the FC method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  RooWorkspace* wspace = new RooWorkspace("wspace");

  ModelConfig* modelConfig = new ModelConfig("FC");
  modelConfig->SetWorkspace(*wspace);
  modelConfig->SetPdf(*model->get_complete_likelihood());
  modelConfig->SetPriorPdf(*model->get_POI_prior());
  modelConfig->SetParametersOfInterest(*model->get_POI_set());
  //modelConfig->SetParametersOfInterest(*wspace->set("poi"));
  //modelConfig->SetNuisanceParameters(*wspace->set("nuis"));
  // modelConfig->SetNuisanceParameters();
  modelConfig->SetNuisanceParameters(*model->get_nuisance_set());

  RooDataSet* data = model->get_data();
  RooArgSet* poi= model->get_POI_set();
  //configure the calculator
  //model->Print();



  cout<<" POI size "<<model->get_POI_set()->getSize()<<endl; 

  // use FeldmaCousins (takes ~20 min)  
  FeldmanCousins fc(*data, *modelConfig);
  fc.SetConfidenceLevel(0.95); //0.9 central limit=0.95 upper limit
  //fc.SetTestSize(.1); // set size of test
  //number counting: dataset always has 1 entry with N events observed
  fc.FluctuateNumDataEntries(false); 
  fc.UseAdaptiveSampling(true);

  fc.SetNBins(200);
  PointSetInterval* fcInt = NULL;
  //ConfInterval* interval = 0;


  RooRealVar* firstPOI = (RooRealVar*) modelConfig->GetParametersOfInterest()->first();

  //  if(doFeldmanCousins){ // takes 7 minutes
  fcInt = (PointSetInterval*) fc.GetInterval(); // fix cast
  //xs}
  //interval = (PointSetInterval*) fc.GetInterval();

  cout<<" ["<<fcInt->LowerLimit( *firstPOI ) << ", " <<
  fcInt->UpperLimit( *firstPOI ) << "]" << endl;
  cout<<" ["<<fcInt->LowerLimit( *firstPOI ) << ", " <<
  fcInt->UpperLimit( *firstPOI ) << "]" << endl;
    
  double ul=fcInt->UpperLimit( *firstPOI );
  //double ul=interval->UpperLimit( *firstPOI );
  return ul;
}






void central_interval_Bayesian(Model* model,double confidence){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating central interval with the Bayesian method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //configure the calculator
  BayesianCalculator bcalc(*model->get_data(),*model->get_complete_likelihood(),*model->get_POI_set(),*model->get_POI_prior(),model->get_nuisance_set());
  
  //get the interval
  bcalc.SetConfidenceLevel(confidence);
  SimpleInterval* interval = bcalc.GetInterval();
  double ll=interval->LowerLimit();
  double ul=interval->UpperLimit();
  std::cout <<confidence <<"% CL confidence interval: " <<ll<<" , "<< ul<<endl;
}









void significance_Hybrid(Model* model,int n_toys,int random_seed=0){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating significance with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys);

  //get the Hypotestresult
  HybridResult* hcResult = myhc.GetHypoTest();
  double significance = hcResult->Significance();
  //double CLS= hcResult->Cls();
  //double CLSerror= hcResult->ClsError(); 
  
  cout <<"HybridCalculator significance:" << significance<< endl;
}

void UL_significance_Hybrid(Model* model,int n_toys,int random_seed=0,double sig=1){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating significance with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys);

  //RooArgSet* poi= model->get_POI_set();
  //  poi->first()->Set(sig);
  RooRealVar* firstPOI = (RooRealVar*) model->get_POI_set()->first();
  firstPOI->setVal(sig);

  //get the Hypotestresult
  HybridResult* hcResult = myhc.GetHypoTest();
  double significance = hcResult->Significance();
  double CLS= hcResult->CLs();
  double CLB= hcResult->CLb();
  double CLsplusb= hcResult->CLsplusb();
  double CLSerror= hcResult->CLsError(); 
  



  cout<<"POI: "<<sig<<endl;
  cout <<"significance:" << significance<<endl;
  cout<<"CLs: "<<CLS<<endl;
  cout<<"CLb: "<<CLB<<endl;
  cout<<"CLsplusb: "<<CLsplusb<<endl;
  cout<<"CLserror: "<<CLSerror<<endl;

  HybridPlot* plot=hcResult->GetPlot("hcPlot","p Values Plot",100);
  TCanvas *c1=new TCanvas;
  plot->Draw();
  c1->SaveAs("hybrid_REsult");
  
}






void upper_limit_Hybrid_auto_scan(Model* model,double confidence,int n_toys_per_point,double lower_scan_bound, double upper_scan_bound,int random_seed=0,bool useCLS=true,double accuracy=0.005){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys_per_point);
  
  //get the interval calculator
  HypoTestInverter myInverter(myhc,*model->get_POI());
  
  //use the CLS method
  myInverter.UseCLs(useCLS);
  
  //set the confidence
  myInverter.SetTestSize((1-confidence)*2);
  
  //run the auto scan in range lower_scan_bound - upper_scan_bound with accuracy parameter accuracy
  myInverter.RunAutoScan(lower_scan_bound,upper_scan_bound,myInverter.Size()/2,accuracy);
 
  //get the result
  HypoTestInverterResult* results = myInverter.GetInterval();
  
  double upperLimit = results->UpperLimit();
  std::cout <<confidence<< "% upper limit is: " <<  upperLimit << std::endl;
}







void upper_limit_Hybrid_fixed_scan(Model* model,double confidence,int n_toys_per_point,double lower_scan_bound, double upper_scan_bound,int n_steps,int random_seed=0,bool useCLS=true){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys_per_point);
  
  //get the interval calculator
  HypoTestInverter myInverter(myhc,*model->get_POI());
  
  //use the CLS method
  myInverter.UseCLs(useCLS);
  
  //set the confidence
  myInverter.SetTestSize((1-confidence)*2);
  
  //run the fixed scan in range lower_scan_bound - upper_scan_bound with n_steps steps
  myInverter.RunFixedScan(n_steps,lower_scan_bound,upper_scan_bound);
 
  //get the result
  HypoTestInverterResult* results = myInverter.GetInterval();
  
  double upperLimit = results->UpperLimit();
  std::cout <<confidence<< "% upper limit is: " <<  upperLimit << std::endl;
}

void upper_limit_Hybrid_one_point(Model* model,double value_to_run_for,int n_toys,int random_seed=0,bool useCLS=true){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating upper limit with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys);
  
  //get the interval calculator
  HypoTestInverter myInverter(myhc,*model->get_POI());
  
  //use the CLS method
  myInverter.UseCLs(useCLS);
  
  //run one point
  myInverter.RunOnePoint(value_to_run_for);
 }
 
 void central_interval_Hybrid_fixed_scan(Model* model,double confidence,int n_toys_per_point,double lower_scan_bound, double upper_scan_bound,int n_steps,int random_seed=0,bool useCLS=true){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating central interval with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
  //set the random seed
  RooRandom::randomGenerator()->SetSeed(random_seed);
    
   //get the calculator
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
  //define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys_per_point);
  
  //get the interval calculator
  HypoTestInverter myInverter(myhc,*model->get_POI());
  
  //use the CLS method
  myInverter.UseCLs(useCLS);
  
  //set the confidence
  myInverter.SetTestSize(1-confidence);
  
  //run the auto fixed in range lower_scan_bound - upper_scan_bound with n_steps steps
  myInverter.RunFixedScan(n_steps,lower_scan_bound,upper_scan_bound);

 
  //get the result
  HypoTestInverterResult* results = myInverter.GetInterval();
  
  double upperLimit = results->UpperLimit();
  double lowerLimit = results->LowerLimit();
  std::cout <<confidence<<"% interval is: " << lowerLimit<<" , "<< upperLimit << std::endl;
}
 
 void central_interval_Hybrid_auto_scan(Model* model,double confidence,int n_toys_per_point,double lower_scan_bound, double upper_scan_bound,int random_seed=0,bool useCLS=true,double accuracy=0.005){
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  cout<<"Calculating central interval with the Hybrid method"<<endl;
  cout<<"///////////////////////////////////////////////////////////////////////////////////////////"<<endl;
  
   //set the random seed
   RooRandom::randomGenerator()->SetSeed(random_seed);
  
  //get the HybridCalculatorOriginal   
  HybridCalculatorOriginal myhc(*model->get_data(),*model->get_sb_likelihood(),*model->get_b_likelihood());
  
  //for numbercounting experiments
  myhc.PatchSetExtended(false);
  
  //set likelihood ratio as the test statistics
  myhc.SetTestStatistic(1);
  
//   define the systematics to be used
  if (model->get_nuisance_set()) {
    myhc.UseNuisance(true);
    myhc.SetNuisancePdf(*model->get_nuisance_prior_pdf());
    myhc.SetNuisanceParameters(*model->get_nuisance_set());
  } else {
    myhc.UseNuisance(false);                            
  }
  
  //define the number of toys to be done
  myhc.SetNumberOfToys(n_toys_per_point);
  
  //get the interval calculator
  HypoTestInverter myInverter(myhc,*model->get_POI());
  
  //use the CLS method
  myInverter.UseCLs(useCLS);
  
  //set the confidence
  myInverter.SetTestSize(1-confidence);
  //scan the values for X to find the interval
  //requires the search range and the desired accuracy
  myInverter.RunAutoScan(lower_scan_bound,upper_scan_bound,myInverter.Size(),accuracy);
  //get the result
  HypoTestInverterResult* results = myInverter.GetInterval();
  
  double upperLimit = results->UpperLimit();
  double lowerLimit = results->LowerLimit();
  std::cout <<confidence<<"% interval is: " << lowerLimit<<" , "<< upperLimit << std::endl;
  
}
 

  


int main(int argc, char* argv[]){
// int main(){
  if(argc==0){
    cout<<""<<endl;
    return 0;
  }
  string file=argv[1];
 


  Model* test=new Model(file.c_str());
  //Model* test=new Model("test_60_230.txt");
  //Model* test=new Model("test_140_200.txt");
  //Model* test=new Model("MultiLepton_Model_Jt200_CU_DAVIS_ML01.txt");
  
  
   srand((unsigned)time(0));
   int random_integer = rand();
   //cout<<random_integer<<endl;
   cout<<"random_number: "<<"XXXseedXXX"<<endl;

   RooRandom::randomGenerator()->SetSeed(random_integer);


  //test->Print();
  bool bband=false;
  if(bband){
    //generate a random number for the seed
    test->set_poi_const(0);
    RooProdPdf* complete= test->get_complete_likelihood();
    RooArgSet* data= test->get_observable_set();
    //data->cleanup();
    RooDataSet* toys=complete->generate(*data,1);
    //cout<<toys->get()->getRealValue("observation_54")<<endl;
    //toys->printArgs(std::cout);
    test->set_dataset(toys);
    test->set_poi_var(5);
  }

  double currentsignal=1;
  bool bcover=false;
  //test->Print();
  if(bcover){

    //test->set_nuisance_const();
     test->set_nuisance_var();
     test->set_poi_const(currentsignal);
     RooProdPdf* complete= test->get_complete_likelihood();
     RooArgSet* data= test->get_observable_set();
     RooDataSet* toys=complete->generate(*data,1);
     //cout<<toys->get()->getRealValue("observation_54")<<endl;
     //toys->printArgs(std::cout);
     test->set_dataset(toys);
     test->set_nuisance_var();
     test->set_poi_var(currentsignal);
  }





//  central_interval_Profile_Likelihood(test,0.95);  

//  upper_limit_Profile_Likelihood(test,0.95); 
//   test->set_nuisance_var();
   

//upper_limit_Profile_Likelihood(test,0.95,hmm); 
  //significance_Profile_Likelihood(test);
  //  upper_limit_FC(test,0.95);
   

//upper_limit_Bayesian(test,0.95);
  //upper_limit_Bayesian_MCMC(test,0.95,10000000);
   // upper_limit_Bayesian_BAT(test,0.95,100000);
    
  //   central_interval_Bayesian(test,0.95);

//   significance_Hybrid(test,1000,321);

  //UL_significance_Hybrid(test,10000,321,0.);
  //upper_limit_Hybrid_auto_scan(test,0.95,50,0.005,0.015,random_integer);

  //  upper_limit_Hybrid_fixed_scan(test,0.95,1000,0.4,0.6,10,random_integer);

  //  upper_limit_Hybrid_one_point(test,0.50,2000,0);



  //   central_interval_Hybrid_auto_scan(test,0.95,500,0,3,300);

//   central_interval_Hybrid_fixed_scan(test,0.95,1000,0,4,4,300);



  string out="out_"+file;
  ofstream outfile(out.c_str());
  outfile<<"##outputfile created by main_program.C for "<<file<<endl;

//   RooArgSet* data= test->get_observable_set();
//   char* name=new char[1000];
//   for(int nch=0;nch<data->getSize();nch++){
//     sprintf (name, "observation_%d",nch);
//     cout<<name<<" "<<data->getRealValue(name)<<endl;
//    }

//   char* name=new char[1000];
//   std::vector< RooRealVar*>* obs=test->observables;
//   for(int nobs=0;nobs<obs->size();nobs++){
//     sprintf (name, "observation_%d",nobs);
//     cout<<name<<" "<<(*obs)[nobs]->getVal()<<endl;

//   }

// cout<<endl;  
// cout<<"nobs per channel"<<endl;
// test->test();
// cout<<"end of nobs"<<endl;


  double ntot_sig_exp=0;
  std::vector< RooConstVar*>* signal=test->signal;
  for(int nsig=0;nsig<signal->size();nsig++){
    ntot_sig_exp+=(*signal)[nsig]->getVal();

  }

  
  outfile<<"####UpperLimits"<<endl;
  outfile<<"NSig: "<<ntot_sig_exp<<endl;
  bool use_bayes=true;
  bool use_PLL=false;
  bool use_FC=false;
  
  if(use_bayes){
    double UpperLimit_Bayesian = upper_limit_Bayesian_BAT(test,0.95,100000);
    outfile<<"UpperLimit_Bayesian(x): "<<UpperLimit_Bayesian<<endl;
    outfile<<"UpperLimit_Bayesian(Nsig): "<<UpperLimit_Bayesian*ntot_sig_exp<<endl;


  }
  if(use_PLL){
    double UpperLimit_PLL = upper_limit_Profile_Likelihood(test,0.95); 
    outfile<<"UpperLimit_PLL(x): "<<UpperLimit_PLL<<endl;
    outfile<<"UpperLimit_PLL(Nsig): "<<UpperLimit_PLL*ntot_sig_exp<<endl;


  }

 if(use_FC){
    double UpperLimit_FC = upper_limit_FC(test,0.95); 
    outfile<<"UpperLimit_FC(x): "<<UpperLimit_FC<<endl;
    outfile<<"UpperLimit_FC(Nsig): "<<UpperLimit_FC*ntot_sig_exp<<endl;


  }


  outfile.close();
  
  return(0);
  
}

