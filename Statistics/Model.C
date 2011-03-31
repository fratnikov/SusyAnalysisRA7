#include "Model.h"
#include<vector>
#include<string>
#include<sstream>
#include "RooFit.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooPoisson.h"
#include "RooGaussian.h"
#include "RooLognormal.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooArgSet.h"
#include"RooPolynomial.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "TMath.h"
#include "RooRandom.h"
#include "RooPlot.h"
#include "RooGamma.h"
#include "RooRealVar.h"
#include "RooAbsReal.h"
#include "Chameleon.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cstdio>




string int_to_string(int i){
    std::stringstream out;
    out << i;
    return  out.str();
    
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Model::Model():n_channels(0),n_backgrounds(0),n_nuisances(0),range_nuisances(-1),range_POI(-1),range_n_obs(-1),use_nuisances(false),corrupted(true)
{
  POI_set=0;
  observable_set=0;
  nuisance_set=0;
  nuisance_prior_pdf=0;
  POI_prior_pdf=0;
  
  POI=0;
  signal=0;
  background=0;
  observables=0;
  nuisance_names=0;
  nuisance_upper_limit=0;
  nuisance_parameters=0;
  nuisance_widths=0;
  scaling_factors=0;
  nuisance_priors=0;
  sb_means=0;
  b_means=0;
  sb_poissons=0;
  b_poissons=0;
  sb_likelihood=0;
  b_likelihood=0;
  data=0;
}

Model::Model(const char* config_file){
  
  POI_set=0;
  observable_set=0;
  nuisance_set=0;
  nuisance_prior_pdf=0;
  POI_prior_pdf=0;
  
  POI=0;
  signal=0;
  background=0;
  observables=0;
  nuisance_names=0;
  nuisance_upper_limit=0;
  nuisance_parameters=0;
  nuisance_widths=0;
  scaling_factors=0;
  nuisance_priors=0;
  sb_means=0;
  b_means=0;
  sb_poissons=0;
  b_poissons=0;
  sb_likelihood=0;
  b_likelihood=0;
  data=0;
  nuisance_means=0;
  
  //store the input from the file here
  vector<double> *signal_expectation =new vector<double>;
  vector< vector<double>* > *background_expectations =new vector< vector<double>* >;
  vector< vector< vector<double>* >* >* systematic_uncertainties=0;
  vector<int> *n_input=new vector<int>;

  //open the config file
  ConfigFile cf(config_file);

  
  //read [definitions]
  this->n_channels = cf.Value("definitions","n_channels");
  this->n_backgrounds = cf.Value("definitions","n_backgrounds");
  this->n_nuisances = cf.Value("definitions","n_nuisance");
  this->range_nuisances= cf.Value("definitions","nuisance_range");
  this->range_POI= cf.Value("definitions","parameter_of_interest_range");
  this->range_n_obs= cf.Value("definitions","observation_range");
  
  
  //read [observation] 
  //fill the vector with the observations
  for(int i=1;i<=n_channels;i++){
    string value_id = (string)"n"+int_to_string(i);
    int value = cf.Value("observation",value_id.c_str());
//     cout<<value_id.c_str()<<" "<<value<<endl;
    n_input->push_back(value);
  }
  
  //read [signal yield] 
  //fill the vector with the signal expectations
  for(int i=1;i<=n_channels;i++){
    string value_id = (string)"s"+int_to_string(i);
    double value = cf.Value("signal_yield",value_id.c_str());
//     cout<<value_id.c_str()<<" "<<value<<endl;
    signal_expectation->push_back(value);
  }
  
  //read [background_yield_n]
  //fill the vectors with the background expectations
   for(int i=1;i<=n_backgrounds;i++){
        string section_id = (string)"background_yield_" + int_to_string(i);
	   vector<double>* background_yield = new vector<double>;	
	   for(int j=1;j<=n_channels;j++){
	     string value_id = (string)"b" + int_to_string(j);
	     double value = cf.Value(section_id.c_str(),value_id.c_str());
// 	     cout<<value_id.c_str()<<" "<<value<<endl;
	     background_yield->push_back(value);
	   }
	   background_expectations->push_back(background_yield);
   }
   
   //read [nuisance_n]
   //fill the object for the systematic uncertainties
   if(this->n_nuisances==0){
     systematic_uncertainties=0;
   }
   else{
     systematic_uncertainties=new vector< vector< vector<double>* >* >;
     this->nuisance_names=new vector<string>;
     this->nuisance_upper_limit=new vector<double>;
      //read [nuisance_n]
      for(int i=1;i<=n_nuisances;i++){  
	vector< vector<double>* >* nuisance_yields=new vector<vector<double>*>;
	string section_id = (string)"nuisance_" + int_to_string(i);
	string name=cf.Value(section_id.c_str(),"name");
	this->nuisance_names->push_back(name);
	//upper range for uncertainties -> (X*sigma)
	double upper_limit=cf.Value(section_id.c_str(),"upper_limit");
	this->nuisance_upper_limit->push_back(upper_limit);

	vector<double>* nuisance_yield = new vector<double>;
	for(int j=1;j<=n_channels;j++){
	  string value_id = (string)"sigma_s" + int_to_string(j);
	  double value = cf.Value(section_id.c_str(),value_id.c_str());
	  nuisance_yield->push_back(value);
// 	  cout<<value_id.c_str()<<" "<<value<<endl;
	}
	nuisance_yields->push_back(nuisance_yield);
	for(int k=1;k<=n_backgrounds;k++){
	  vector<double>* nuisance_yield = new vector<double>;
	  for(int j=1;j<=n_channels;j++){
	    string value_id = (string)"sigma_b" + int_to_string(k) + "_" + int_to_string(j);
	    double value = cf.Value(section_id.c_str(),value_id.c_str());
	    nuisance_yield->push_back(value);
// 	         cout<<value_id.c_str()<<" "<<value<<endl;
	  }
	  nuisance_yields->push_back(nuisance_yield);
	}
	systematic_uncertainties->push_back(nuisance_yields);
      }
   }

  check_input(n_input,signal_expectation,background_expectations,systematic_uncertainties);
  if(systematic_uncertainties==0){
    use_nuisances=false;
  }
  else use_nuisances=true;
  create_POI();
  create_observables();
  create_signal_expectations(signal_expectation);
  create_background_expectations(background_expectations);
  create_nuisances(systematic_uncertainties);
  create_scaling_factors(systematic_uncertainties);
  create_POI_prior();

  //here make perhaps the decision which distribution to take
  create_nuisance_priors();
  create_sb_likelihood();
  create_b_likelihood();
  create_dataset(n_input);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Model::Model(std::vector<double>* signal_expectation,std::vector< std::vector<double>* >* background_expectation,std::vector< vector< vector<double>* >* >* systematic_uncertainties,std::vector<int>* n_input,int nuisance_range,int POI_range,int observation_range):n_channels(signal_expectation->size()),n_backgrounds(background_expectation->size()),n_nuisances(systematic_uncertainties->size()),range_nuisances(nuisance_range),range_POI(POI_range),range_n_obs(observation_range){
  
  POI_set=0;
  observable_set=0;
  nuisance_set=0;
  nuisance_prior_pdf=0;
  POI_prior_pdf=0;
  
  POI=0;
  signal=0;
  background=0;
  observables=0;
  nuisance_names=0;
  nuisance_upper_limit=0;
  nuisance_parameters=0;
  nuisance_widths=0;
  scaling_factors=0;
  nuisance_priors=0;
  sb_means=0;
  b_means=0;
  sb_poissons=0;
  b_poissons=0;
  sb_likelihood=0;
  b_likelihood=0;
  data=0;
  nuisance_means=0;
  
  check_input(n_input,signal_expectation,background_expectation,systematic_uncertainties);
  if(systematic_uncertainties==0){
    use_nuisances=false;
  }
  else use_nuisances=true;
  create_POI();
  create_observables();
  create_signal_expectations(signal_expectation);
  create_background_expectations(background_expectation);
  create_nuisances(systematic_uncertainties);
  create_scaling_factors(systematic_uncertainties);
  create_POI_prior();
  create_nuisance_priors();
  create_sb_likelihood();
  create_b_likelihood();
  if(n_input!=0){
    create_dataset(n_input);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Model::~Model(){
  if(data!=0){
    delete data;    
  }
  cout<<"deleted"<<endl;
  if(b_likelihood!=0){
    delete b_likelihood;    
  }
  cout<<"deleted"<<endl;
  if(sb_likelihood!=0){
    delete sb_likelihood;    
  }
  cout<<"deleted"<<endl;
  if(b_poissons!=0){
    for(int i=0;i<b_poissons->size();i++){
      delete b_poissons->at(i);   
    }
    delete b_poissons;
  }
  cout<<"deleted"<<endl;
  if(sb_poissons!=0){
    for(int i=0;i<sb_poissons->size();i++){
      delete sb_poissons->at(i);   
    }
    delete sb_poissons;
  }
  cout<<"deleted"<<endl;
  if(b_means!=0){
    for(int i=0;i<b_means->size();i++){
      delete b_means->at(i);    
    }
    delete b_means;
  }
  cout<<"deleted"<<endl;
  if(sb_means!=0){
    for(int i=0;i<sb_means->size();i++){
      delete sb_means->at(i); 
    }
    delete sb_means;
  }
  cout<<"deleted"<<endl;
  if(nuisance_priors!=0){
    for(int i=0;i<nuisance_priors->size();i++){
      delete nuisance_priors->at(i);  
    }
    delete nuisance_priors;
  }
  cout<<"deleted"<<endl;
  if(scaling_factors!=0){
    for(int i=0;i<scaling_factors->size();i++){
      for(int j=0;j<scaling_factors->at(i)->size();j++){
	for(int k=0;k<scaling_factors->at(i)->at(j)->size();k++){
	  delete scaling_factors->at(i)->at(j)->at(k);    
	}
	delete scaling_factors->at(i)->at(j);
      }
      delete scaling_factors->at(i);
    }
    delete scaling_factors;
  }
  cout<<"deleted"<<endl;
  if(nuisance_widths!=0){
    for(int i=0;i<nuisance_widths->size();i++){
      delete nuisance_widths->at(i);  
    }
    delete nuisance_widths;
  }
  cout<<"deleted"<<endl;
  if(nuisance_parameters!=0){
    for(int i=0;i<nuisance_parameters->size();i++){
      delete nuisance_parameters->at(i);  
    }
    delete nuisance_parameters;
  }
  cout<<"deleted"<<endl;
  if(observables!=0){
    for(int i=0;i<observables->size();i++){
      delete observables->at(i);  
    }
    delete observables;
  }
  cout<<"deleted"<<endl;
  if(background!=0){
    for(int i=0;i<background->size();i++){
      for(int j=0;j<background->at(i)->size();j++){
	delete background->at(i)->at(j);
      }
      delete background->at(i);
    }
    delete background;
  }
  cout<<"deleted"<<endl;
  if(signal!=0){
    for(int i=0;i<signal->size();i++){
      delete signal->at(i);    
    }
    delete signal;
  }
  cout<<"deleted"<<endl;
  if(POI!=0){
    delete POI;
  }
  cout<<"deleted"<<endl;
  if(POI_prior_pdf!=0){
    delete POI_prior_pdf;
  }
  cout<<"deleted"<<endl;
  if(nuisance_prior_pdf!=0){
    delete nuisance_prior_pdf;
  }
  cout<<"deleted"<<endl;
  if(nuisance_set!=0){
    delete nuisance_set;
  }
  cout<<"deleted"<<endl;
  if(observable_set!=0){
    delete observable_set;
  }
  cout<<"deleted"<<endl;
  if(POI_set!=0){
    delete POI_set;
  }
  cout<<"deleted"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Model::check_input(std::vector<int>* n_input,std::vector<double>* signal_expectation,std::vector< std::vector<double>* >* background_expectation,std::vector< std::vector< std::vector<double>* >* >* systematic_uncertainties){
  
  cout<<"Checking, if input is consistent\n"<<endl;
  int n=signal_expectation->size();
  for(int i=0;i<background_expectation->size();i++){
    if(background_expectation->at(i)->size()!=n){
      this->corrupted=true;
      cout<<"ERROR:		size of signal and background expectation "<<i<<" don't match"<<endl;
      return(false);
    }    
  }
  if(n_input!=0){
    if(n_input->size()!=n){
      this->corrupted=true;
      cout<<"ERROR:		size of signal expectation and observation don't match"<<endl;
      return(false);      
    }    
  }
  if(systematic_uncertainties!=0){
    for(int i=0;i<systematic_uncertainties->size();i++){
      if(systematic_uncertainties->at(i)->size()!=background_expectation->size()+1){
	this->corrupted=true;
	cout<<"ERROR:		 systematic uncertainty matrix doesn't contain values for signal and all backgrounds"<<endl;
	return(false);
      }      
      for(int j=0;j<systematic_uncertainties->at(i)->size();j++){
	if(systematic_uncertainties->at(i)->at(j)->size()!=n){
	  this->corrupted=true;
	  cout<<"ERROR:		size of signal expectationand systematic uncertainty matrix don't match"<<endl;
	  return(false);
	}
      }
    }
  }
  this->corrupted=false;
  return(true);
}
// this overwrites existing dataset
void Model::set_dataset(RooDataSet* d){
  delete data;
  data=d;

}

///set nuisances to zero andconstant
void Model::set_nuisance_const(){
  
 RooArgSet* nuisances=nuisance_set;
 TIterator* it=nuisances->createIterator();
 //RooAbsArg* nui;
 // while((RooAbsReal*)it->Next()){
 RooRealVar* nui;
 while(nui=(RooRealVar*)it->Next()){
   //(RooAbsReal*)it->setVal(0);
   RooRealVar* nui2=dynamic_cast<RooRealVar*>(nui);
   //cout<<"nui "<<nui2<<endl;
   nui2->setVal(0);
   nui2->setConstant(kTRUE);
   
   
 }

 
}
///set nuisances to zero andconstant
void Model::set_nuisance_var(){
  
 RooArgSet* nuisances=nuisance_set;
 TIterator* it=nuisances->createIterator();
 RooRealVar* nui;
 // while((RooAbsReal*)it->Next()){
 while(nui=(RooRealVar*)it->Next()){
   //(RooAbsReal*)it->setVal(0);
   RooRealVar* nui2=dynamic_cast<RooRealVar*>(nui);
   //cout<<"nui "<<nui2<<endl;
   nui2->setVal(0);
   nui2->setConstant(kFALSE);
   
   
 }

}

void Model::set_poi_const(double p=0){
  RooRealVar* ss=get_POI();
  ss->setVal(p);
  ss->setConstant(kTRUE);


}
void Model::set_poi_var(double p=0){
  RooRealVar* ss=get_POI();  
  ss->setVal(p);
  ss->setConstant(kFALSE);

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_observables(){
 cout<<"Create observables\n"<<endl; 
 if(range_n_obs>0){
   observables=new vector<RooRealVar*>;
   observable_set=new RooArgSet();
   char* name=new char[1000];
   
   for(int i=0;i<this->n_channels;i++){
     sprintf (name, "observation_%d",i);
     RooRealVar* tmp_observables=new RooRealVar(name,name,0,range_n_obs);
     observables->push_back(tmp_observables); 
     observable_set->add(*observables->at(i));
   }      
   delete [] name;
 }
 else{
   cout<<"ERROR:	negative range for the observations\n"<<endl;
   this->corrupted=true;
 }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_signal_expectations(std::vector<double>* signal_expectation){
  cout<<"Create signal expectations\n"<<endl;
  signal=new std::vector< RooConstVar*>;
  char* name=new char[1000];
  
  for(int i=0;i<this->n_channels;i++){
    sprintf (name, "signal_%d", i);
    RooConstVar* tmp_signal=new RooConstVar(name,name,signal_expectation->at(i));
    signal->push_back(tmp_signal);
  }
  delete [] name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_background_expectations(std::vector< std::vector<double>* >* background_expectation){
  cout<<"Create background expectations\n"<<endl;
  background =new vector< vector<RooConstVar*>* >;
  char* name=new char[1000];
  
  for(int i=0;i<this->n_backgrounds;i++){
    vector<RooConstVar*>* tmp_background_row=new vector<RooConstVar*>;
    for(int j=0;j<this->n_channels;j++){
      sprintf (name, "background_channel_%d_source_%d",j,i);
      RooConstVar* tmp_background=new RooConstVar(name,name,background_expectation->at(i)->at(j));
      tmp_background_row->push_back(tmp_background);
    }
    background->push_back(tmp_background_row);
  }
  delete [] name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_nuisances(std::vector< vector< vector<double>* >* >* systematic_uncertainties){
   cout<<"Create nuisance parameters\n"<<endl;
   if(range_nuisances>0){
     if(use_nuisances==true){   
       
       nuisance_set=new RooArgSet();
       nuisance_parameters=new vector<RooRealVar*>;
       nuisance_widths=new vector<RooConstVar*>;
       char* name=new char[1000];      
       char* title=new char[1000];
       
       for(int i=0;i<systematic_uncertainties->size();i++){
	 double greatest_error=0;
	 for(int j=0;j<systematic_uncertainties->at(i)->size();j++){
	   for(int k=0;k<systematic_uncertainties->at(i)->at(j)->size();k++){
	     if(systematic_uncertainties->at(i)->at(j)->at(k) >greatest_error){
	       greatest_error=systematic_uncertainties->at(i)->at(j)->at(k);	  
	     }
	   }
	 }
	 if(nuisance_names==0){
	   sprintf (name, "sigma_%d", i);
	   sprintf (title, "sigma_%d", i);
	 }
	 else{
	   sprintf (name, "sigma_%d", i);
	   sprintf (title, "sigma_%s", this->nuisance_names->at(i).c_str());
	 }
	 RooConstVar* tmp_nuisance_width=new RooConstVar(name,title,greatest_error);
	 nuisance_widths->push_back(tmp_nuisance_width);
	 if(nuisance_names==0){
	   sprintf (name, "delta_%d", i);
	   sprintf (title, "delta_%d", i);
	 }
	 else{
	   sprintf (name, "delta_%d", i);
	   sprintf (title, "delta_%s", this->nuisance_names->at(i).c_str());
	 }
	 //RooRealVar* tmp_nuisance_parameters=new RooRealVar(name,title,0,-1*range_nuisances*nuisance_widths->at(i)->getVal(),1.0*range_nuisances*nuisance_widths->at(i)->getVal());
	 //RooRealVar* tmp_nuisance_parameters=new RooRealVar(name,title,0,-1,1.0*range_nuisances*nuisance_widths->at(i)->getVal());
	 
	 double lower_limit=-1;
	  std::string line = title;
	 std::string::size_type pos=line.find("[LOGNORMAL]");
	 if(pos != std::string::npos) lower_limit=-0.9999;
	 RooRealVar* tmp_nuisance_parameters=new RooRealVar(name,title,0,lower_limit,1.0*nuisance_upper_limit->at(i)*nuisance_widths->at(i)->getVal());
	 cout<<name<<" has upper limit "<<nuisance_upper_limit->at(i)<<endl;

	 nuisance_parameters->push_back(tmp_nuisance_parameters);
	 nuisance_set->add(*nuisance_parameters->at(i));              
       }
       delete [] name;
       delete [] title;
     }
     else cout<<"No systematic uncertainties specified, no nuisance parameters created\n"<<endl;
   }
   else{
     cout<<"ERROR:	negative range for the nuisance_parameters\n"<<endl;
     this->corrupted=true;
   }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_scaling_factors(vector< vector< vector<double>* >* >* systematic_uncertainties){
  cout<<"Create scaling factors for nuisances\n"<<endl;
  if(use_nuisances==true &&nuisance_parameters!=0){     
    
    scaling_factors = new vector< vector< vector<RooConstVar*>* >* >;
    char* name=new char[1000]; 
  
    for(int i=0;i<nuisance_parameters->size();i++){
      
      vector< vector<RooConstVar*>* >*  tmp_scaling_factors_for_one_nuisance = new vector< vector<RooConstVar*>* >;
      vector<RooConstVar*>* tmp_signal_scaling_for_one_nuisance = new vector<RooConstVar*>;

      for(int j=0;j<this->n_channels;j++){
	sprintf (name, "signal_scaling_factor_channel_%d_nuisance_%d", j,i);
	RooConstVar* tmp_signal_scaling=new RooConstVar(name,name,1.0*systematic_uncertainties->at(i)->at(0)->at(j)/nuisance_widths->at(i)->getVal());
	tmp_signal_scaling_for_one_nuisance->push_back(tmp_signal_scaling);
      }
      tmp_scaling_factors_for_one_nuisance->push_back(tmp_signal_scaling_for_one_nuisance);

      for(int j=0;j<background->size();j++){
	
	vector<RooConstVar*>* tmp_background_scaling_for_one_nuisance_for_one_background_source = new vector<RooConstVar*>;
	
	for(int k=0;k<this->n_channels;k++){
	  sprintf (name, "background_scaling_factor_channel_%d_source_%d_nuisance_%d",k,j,i);
	  RooConstVar* tmp_background_scaling=new RooConstVar(name,name,1.0*systematic_uncertainties->at(i)->at(j+1)->at(k)/nuisance_widths->at(i)->getVal());
	  tmp_background_scaling_for_one_nuisance_for_one_background_source->push_back(tmp_background_scaling);
	}
	tmp_scaling_factors_for_one_nuisance->push_back(tmp_background_scaling_for_one_nuisance_for_one_background_source);
      }
      scaling_factors->push_back(tmp_scaling_factors_for_one_nuisance);
    }
    delete [] name;
  }
  else{
    if(use_nuisances==true){
      cout<<"ERROR: systematics specified, but no nuisance parameters created yet; can't define scaling factors\n"<<endl;
      this->corrupted=true;
    }
    else cout<<"No systematics_specified, no scaling factors needed\n"<<endl;
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use this for Gaussian errors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_nuisance_priors(){
  //void Model::create_nuisance_priors(){
  cout<<"Create nuisances priors\n"<<endl;  
  if(use_nuisances==true &&nuisance_parameters!=0){
    
    nuisance_priors=new vector<RooAbsPdf*>;
    nuisance_means=new vector<RooFormulaVar*>;
    RooArgList* nuisance_prior_list=new RooArgList();
    char* name=new char[1000]; 
    
    for(int i=0;i<nuisance_parameters->size();i++){
      //here check if in name is gauss or logNormal
      //cout<<(*nuiscance_parameters)[i].GetTitle()<<endl;
      RooRealVar* dummy = nuisance_parameters->at(i);
      //cout<<dummy->GetTitle()<<endl;
      
      int distribution=0;
      std::string line = dummy->GetTitle();///now find in string gauss or logNormal
      std::string::size_type pos=line.find("[GAUSS]");
      if(pos != std::string::npos) distribution=0;
      pos=line.find("[LOGNORMAL]");
      if(pos != std::string::npos) distribution=1;
      
      if(distribution==0){
	///using gaussian function as nuisance distribution
	cout<<" ---> "<<line<<" using Gaussian Distribuion"<<endl;
	sprintf (name, "nuisance_prior_%d", i);
	RooGaussian* tmp_nuisance_priors=new RooGaussian(name,name,*nuisance_parameters->at(i),RooFit::RooConst(0),*nuisance_widths->at(i));
	nuisance_priors->push_back(tmp_nuisance_priors);
	nuisance_prior_list->add(*nuisance_priors->at(i));
      }
      else if(distribution==1){ 
	///using logNormal function as nuiscance distribution
	cout<<" ---> "<<line<<" using logNormal Distribuion"<<endl;
	char* name2=new char[1000]; 

	sprintf (name, "nuisance_mean_%d", i);
	sprintf(name2,"%s+1",nuisance_parameters->at(i)->GetName());
	RooFormulaVar* tmp_nuisance_means=new RooFormulaVar(name,name2,RooArgSet(*nuisance_parameters->at(i)));
	nuisance_means->push_back(tmp_nuisance_means);
	sprintf (name, "nuisance_prior_%d", i);
 	//RooLognormal* tmp_nuisance_priors=new RooLognormal(name, name,*nuisance_means->at(i), RooFit::RooConst(1), RooFit::RooConst(TMath::Exp(nuisance_widths->at(i)->getVal())));
	//ok i have to adjust my mean parameter or each nusiance....
	///by my handmade calculations this is mu=sigma^2
	double new_mean=nuisance_widths->at(i)->getVal()*nuisance_widths->at(i)->getVal();
	//and put it into the function as exponential...
	RooLognormal* tmp_nuisance_priors=new RooLognormal(name, name,*nuisance_means->at(i), RooFit::RooConst(TMath::Exp(new_mean)), RooFit::RooConst(TMath::Exp(nuisance_widths->at(i)->getVal())));
	//cout<<"----------------------------"<<name<<" "<<nuisance_widths->at(i)->getVal()<<" "<<TMath::Exp(nuisance_widths->at(i)->getVal())<<endl;
	nuisance_priors->push_back(tmp_nuisance_priors);
	nuisance_prior_list->add(*nuisance_priors->at(i));


      }
    }
    nuisance_prior_pdf=new RooProdPdf("nuisance_prior_pdf","nuisance_prior_pdf",*nuisance_prior_list);
    delete nuisance_prior_list;
    delete [] name;
  }
  else{
    if(use_nuisances==true){
      cout<<"ERROR: systematics specified, but no nuisance parameters created yet; can't create nuisance pdfs\n"<<endl;
      this->corrupted=true;
    }
    else cout<<"No systematics_specified, no nuisance_priors needed\n"<<endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use this for Gaussian errors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void Model::create_nuisance_priors(){
//   //void Model::create_nuisance_priors(){
//   cout<<"Create nuisances priors\n"<<endl;  
//   if(use_nuisances==true &&nuisance_parameters!=0){
    
//     nuisance_priors=new vector<RooAbsPdf*>;
//     RooArgList* nuisance_prior_list=new RooArgList();
//     char* name=new char[1000]; 
    
//     for(int i=0;i<nuisance_parameters->size();i++){
//       sprintf (name, "nuisance_prior_%d", i);
//       RooGaussian* tmp_nuisance_priors=new RooGaussian(name,name,*nuisance_parameters->at(i),RooFit::RooConst(0),*nuisance_widths->at(i));
//       nuisance_priors->push_back(tmp_nuisance_priors);
//       nuisance_prior_list->add(*nuisance_priors->at(i));
//     }
//     nuisance_prior_pdf=new RooProdPdf("nuisance_prior_pdf","nuisance_prior_pdf",*nuisance_prior_list);
//     delete nuisance_prior_list;
//     delete [] name;
//   }
//   else{
//     if(use_nuisances==true){
//       cout<<"ERROR: systematics specified, but no nuisance parameters created yet; can't create nuisance pdfs\n"<<endl;
//       this->corrupted=true;
//     }
//     else cout<<"No systematics_specified, no nuisance_priors needed\n"<<endl;
//   }
// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Use this for LogNormal errors
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_nuisance_priors_2(){
     if(use_nuisances==true &&nuisance_parameters!=0){
     
     nuisance_priors=new vector<RooAbsPdf*>;
     nuisance_means=new vector<RooFormulaVar*>;
     RooArgList* nuisance_prior_list=new RooArgList();
     char* name=new char[1000]; 
     
     for(int i=0;i<nuisance_parameters->size();i++){
       char* name2=new char[1000]; 
       sprintf (name, "nuisance_mean_%d", i);
       sprintf(name2,"%s+1",nuisance_parameters->at(i)->GetName());
       RooFormulaVar* tmp_nuisance_means=new RooFormulaVar(name,name2,RooArgSet(*nuisance_parameters->at(i)));
       nuisance_means->push_back(tmp_nuisance_means);
       sprintf (name, "nuisance_prior_%d", i);
       RooLognormal* tmp_nuisance_priors=new RooLognormal(name, name,*nuisance_means->at(i), RooFit::RooConst(1), RooFit::RooConst(TMath::Exp(nuisance_widths->at(i)->getVal())));

       nuisance_priors->push_back(tmp_nuisance_priors);
       nuisance_prior_list->add(*nuisance_priors->at(i));
       delete [] name2;
     }
     nuisance_prior_pdf=new RooProdPdf("nuisance_prior_pdf","nuisance_prior_pdf",*nuisance_prior_list);
     delete nuisance_prior_list;
     delete [] name;
   }
   else{
     if(use_nuisances==true){
       cout<<"ERROR: systematics specified, but no nuisance parameters created yet; can't create nuisance pdfs\n"<<endl;
       this->corrupted=true;
     }
     else cout<<"No systematics_specified, no nuisance_priors needed\n"<<endl;
   }
 }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Use this for Gamma errors, does not work
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void Model::create_nuisance_priors(){
//   
//   if(use_nuisances==true &&nuisance_parameters!=0){
//     
//     nuisance_priors=new vector<RooAbsPdf*>;
//     nuisance_means=new vector<RooFormulaVar*>;
//     RooArgList* nuisance_prior_list=new RooArgList();
//     char* name=new char[1000]; 
//     RooConstVar gamma("gamma","gamma",20);
//     
//     for(int i=0;i<nuisance_parameters->size();i++){
//       char* name2=new char[1000]; 
//       sprintf (name, "beta_%d", i);
//       RooConstVar* beta=new RooConstVar(name,name,TMath::Sqrt(nuisance_widths->at(i)->getVal()*nuisance_widths->at(i)->getVal()/gamma.getVal()));
//       sprintf(name2,"%s+beta_%d*gamma",nuisance_parameters->at(i)->GetName(),i);
//       nuisance_parameters->at(i)->setRange(TMath::Max(-1.0,-beta->getVal()*gamma.getVal()),range_nuisances*nuisance_widths->at(i)->getVal());
//       sprintf (name, "nuisance_mean_%d", i);
//       RooFormulaVar* tmp_nuisance_means=new RooFormulaVar(name,name2,RooArgSet(*beta,gamma,*nuisance_parameters->at(i)));
//       nuisance_means->push_back(tmp_nuisance_means);
//       sprintf (name, "nuisance_prior_%d", i);
//       RooGamma* tmp_nuisance_priors=new RooGamma(name, name,*nuisance_means->at(i),RooFit::RooConst(gamma.getVal()),RooFit::RooConst(beta->getVal()),RooFit::RooConst(0));
//       tmp_nuisance_priors->Print();
//       nuisance_priors->push_back(tmp_nuisance_priors);
//       nuisance_prior_list->add(*nuisance_priors->at(i));
//       delete [] name2;
//       delete beta;
//     }
//     nuisance_prior_pdf=new RooProdPdf("nuisance_prior_pdf","nuisance_prior_pdf",*nuisance_prior_list);
//     nuisance_prior_pdf->Print();
//     delete nuisance_prior_list;
//     delete [] name;
//   }
//   else{
//     if(use_nuisances==true){
//       cout<<"ERROR: systematics specified, but no nuisance parameters created yet; can't create nuisance pdfs\n"<<endl;
//       this->corrupted=true;
//     }
//     else cout<<"No systematics_specified, no nuisance_priors needed\n"<<endl;
//   }
// }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_POI(){
  if(range_POI>0){
    cout<<"Create parameter of interest\n"<<endl;
    //POI=new RooRealVar("POI","POI",1.0*range_POI/2,0,range_POI);
    POI=new RooRealVar("POI","POI",1.0*range_POI/2,0,range_POI);
    POI_set=new RooArgSet(*POI);
  }
  else{
    cout<<"ERROR:	negative range specified, problem with input\n"<<endl;
    this->corrupted=true;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_POI_prior(){
  if(POI!=0){
    cout<<"Create flat prior for the parameter of interest\n"<<endl;
    RooAbsPdf* tmp_POI_prior= new RooPolynomial("tmp_POI_pior","tmp_POI_pior",*POI,RooArgList(RooFit::RooConst(0)));  
    //RooJeffreysPrior* tmp_POI_prior =new RooJeffreysPrior("jeffreys","jeffreys",*w.pdf("p"),*POI,*observable_set);
    //RooJeffreysPrior pi("jeffreys","jeffreys",*w.pdf("p"),*w.set("poi"),*w.set("obs"));
  
//     tmp->Print();
    POI_prior_pdf=new RooProdPdf("POI_prior","POI_prior",RooArgList(*tmp_POI_prior));
    POI_prior_pdf->getVal();
    delete tmp_POI_prior;
  }
  else{
    cout<<"ERROR:	no parameter of interest specified yet, can't create prior\n"<<endl;
    this->corrupted=true;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_sb_likelihood(){
  if(corrupted==false){
    cout<<"Create sb_likelihood\n"<<endl;
    sb_means = new vector<RooFormulaVar*>;
    sb_poissons = new vector<RooPoisson*>;
    vector<RooArgSet*>* sb_params =new vector<RooArgSet*>;
    char* name=new char[1000]; 
  
    for(int i=0;i<n_channels;i++){
      RooArgSet* tmp_sb_params=new RooArgSet(*POI,*signal->at(i));
      for(int j=0;j<n_backgrounds;j++){
        tmp_sb_params->add(*background->at(j)->at(i));
        if(use_nuisances==true){
  	  for(int k=0;k<nuisance_parameters->size();k++){
	    tmp_sb_params->add(*nuisance_parameters->at(k));
	    tmp_sb_params->add(*scaling_factors->at(k)->at(0)->at(i));
	    tmp_sb_params->add(*scaling_factors->at(k)->at(j+1)->at(i));
	  }
        }
      }
      sb_params->push_back(tmp_sb_params);
    }
    //Poisson means and Poisson distributions
    stringstream* formula_string=new stringstream();  
    for(int i=0;i<n_channels;i++){
      formula_string->str("");
      *formula_string<<"POI";
      *formula_string<<"*signal_"<<i;
      if(use_nuisances==true){
        for(int j=0;j<nuisance_parameters->size();j++){
	  *formula_string<<"*(1+delta_"<<j<<"*signal_scaling_factor_channel_"<<i<<"_nuisance_"<<j<<")";
        }
      }
      for(int k=0;k<n_backgrounds;k++){
        *formula_string<<"+background_channel_"<<i<<"_source_"<<k;
        if(use_nuisances==true){	
	  for(int j=0;j<nuisance_parameters->size();j++){
	    *formula_string<<"*(1+delta_"<<j<<"*background_scaling_factor_channel_"<<i<<"_source_"<<k<<"_nuisance_"<<j<<")";
	  }
        }
      }
      sprintf (name, "sb_mean_%d",i);
      RooFormulaVar* tmp_sb_means=new RooFormulaVar(name,formula_string->str().c_str(),*sb_params->at(i));
      sb_means->push_back(tmp_sb_means);
      sprintf (name, "sb_poisson_%d",i);
      RooPoisson* tmp_sb_poissons=new RooPoisson(name,name,*observables->at(i),*sb_means->at(i));
      sb_poissons->push_back(tmp_sb_poissons);
    }
  
    RooArgList *sb_pdfs=new RooArgList();
    for(int i=0;i<n_channels;i++)  {
      sb_pdfs->add(*sb_poissons->at(i));
    }
    sb_likelihood=new RooProdPdf("sb_likelihood","sb_likelihood",*sb_pdfs);
    
    delete sb_pdfs;
    for(int i=0;i<sb_params->size();i++){
      delete sb_params->at(i);
    }
    delete sb_params;
    delete formula_string;
    delete [] name;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::create_b_likelihood(){
  
  if(corrupted==false){
    cout<<"Create b_likelihood\n"<<endl;
    b_means = new vector<RooFormulaVar*>;
    b_poissons = new vector<RooPoisson*>;
    vector<RooArgSet*>* b_params =new vector<RooArgSet*>;
    char* name=new char[1000];   
    for(int i=0;i<n_channels;i++){
      RooArgSet* tmp_b_params=new RooArgSet();
      for(int j=0;j<n_backgrounds;j++){
	tmp_b_params->add(*background->at(j)->at(i));
	if(use_nuisances==true){
	  for(int k=0;k<nuisance_parameters->size();k++){
	    tmp_b_params->add(*nuisance_parameters->at(k));
	    tmp_b_params->add(*scaling_factors->at(k)->at(j+1)->at(i));
	  }
	}
      }
      b_params->push_back(tmp_b_params);
    }
    //Poisson means and Poisson distributions
    stringstream* formula_string=new stringstream();  
    for(int i=0;i<n_channels;i++){
      formula_string->str("");
      for(int k=0;k<n_backgrounds;k++){
	if(k==0){
	  *formula_string<<"background_channel_"<<i<<"_source_"<<k;
	}
	else{
	  *formula_string<<"+background_channel_"<<i<<"_source_"<<k;
	}
	if(use_nuisances==true){
	  for(int j=0;j<nuisance_parameters->size();j++){
	    *formula_string<<"*(1+delta_"<<j<<"*background_scaling_factor_channel_"<<i<<"_source_"<<k<<"_nuisance_"<<j<<")";
	  }
	}      
      }
      sprintf (name, "b_mean_%d",i);
      RooFormulaVar* tmp_b_means=new RooFormulaVar(name,formula_string->str().c_str(),*b_params->at(i));
      b_means->push_back(tmp_b_means);
      sprintf (name, "b_poisson_%d",i);
      RooPoisson* tmp_b_poissons=new RooPoisson(name,name,*observables->at(i),*b_means->at(i));
      b_poissons->push_back(tmp_b_poissons);
    }
    RooArgList *b_pdfs=new RooArgList();
    for(int i=0;i<n_channels;i++)  {
      b_pdfs->add(*b_poissons->at(i));
    }
    b_likelihood=new RooProdPdf("b_likelihood","b_likelihood",*b_pdfs);
    delete b_pdfs;
    for(int i=0;i<b_params->size();i++){
      delete b_params->at(i);
    }
    delete b_params;
    delete formula_string;
    delete [] name;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Model::create_dataset(std::vector<int>* n_input){
  if(corrupted==false){  
    cout<<"Create data from input\n"<<endl;
    if(n_input->size()!=n_channels){
      cout<<"ERROR:	observation input doesn't match number of channels\n"<<endl;
      this->corrupted=true;
      return(false);
    }
    for(int i=0;i<n_channels;i++){
      observables->at(i)->setVal(n_input->at(i));  
    }
    if(data!=0){
      delete data;
    }
    data=new RooDataSet("data","data",*observable_set);
    data->add(*observable_set);
    return (true);
  }
  return(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooRealVar* Model::get_POI(){
 return(this->POI); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooArgSet* Model::get_POI_set(){
 return(this->POI_set); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooArgSet* Model::get_observable_set(){
 return(this->observable_set); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooArgSet* Model::get_nuisance_set(){
 return(this->nuisance_set); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooProdPdf* Model::get_POI_prior(){
  return(POI_prior_pdf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooProdPdf* Model::get_nuisance_prior_pdf(){
  return(nuisance_prior_pdf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooProdPdf* Model::get_sb_likelihood(){
  return(sb_likelihood);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooProdPdf* Model::get_b_likelihood(){
  return(this->b_likelihood);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooProdPdf* Model::get_complete_likelihood(){
  RooProdPdf* complete_likelihood=new RooProdPdf("complete_likelihood","complete_likelihood",RooArgList(*this->sb_likelihood,*this->nuisance_prior_pdf));
  return(complete_likelihood);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RooDataSet* Model::get_data(){
  return(this->data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::set_random_seed(int i){
 cout<<"Setting random seed to "<<i<<endl;
 RooRandom::randomGenerator()->SetSeed(i);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::Print(){
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Some output of the model parameters
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"Model information"<<endl;
  cout<<"---------------------------------------------------------------------------------------------------------------------\n\n\n"<<endl;
  cout<<"Number of channels:	"<<this->n_channels<<"\nNumber of background sources per channel:	"<<this->n_backgrounds<<"\n\n\n"<<endl;
  cout<<"Channel		signal expectation			background_expectation(s)\n"<<endl;
  for(int i=0;i<this->n_channels;i++){
   cout<<i<<"			"<<this->signal->at(i)->getVal();
   for(int j=0;j<this->n_backgrounds;j++){
     cout<<"				"<<this->background->at(j)->at(i)->getVal(); 
   }
   cout<<"\n";
  }
  
  if(use_nuisances==true){
    cout<<"\n\n---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Systematic uncertainties"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------\n\n"<<endl;
    for(int i=0;i<this->nuisance_parameters->size();i++){
      cout<<"Matrix for "<<nuisance_names->at(i).c_str()<<" uncertainty "<<"\n"<<endl; 
      cout<<"			sigma_signal		sigma_b\n"<<endl;
      for(int j=0;j<this->n_channels;j++){
	cout<<"Channel "<<j<<"		";
	for(int k=0;k<this->n_backgrounds+1;k++){
	  cout<<this->nuisance_widths->at(i)->getVal()*this->scaling_factors->at(i)->at(k)->at(j)->getVal()<<"			";
	}
	cout<<"\n";
      }
      cout<<"\n\n";
    }
    cout<<"\n\n---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"scaling factors"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------\n\n\n"<<endl;
    for(int i=0;i<nuisance_parameters->size();i++){
      cout<<"Scaling factors for "<<nuisance_names->at(i).c_str()<<" nuisance parameter "<<"\n"<<endl;
      cout<<"Width of nuisance distribution: "<<nuisance_widths->at(i)->getVal()<<"\n"<<endl;
      cout<<"		signal scaling		background scaling\n"<<endl;
      for(int j=0;j<n_channels;j++){
	cout<<"channel "<<j<<"	"<<scaling_factors->at(i)->at(0)->at(j)->getVal();
	for(int k=0;k<background->size();k++){
	  cout<<"		"<<scaling_factors->at(i)->at(k+1)->at(j)->getVal();
	}
	cout<<"\n"<<endl;
      }
      cout<<"\n\n\n"<<endl;
    }
  }
}



void Model::test(string file){
  ofstream myfile;
  myfile.open (file.c_str(), fstream::app);
  myfile<<endl;
  myfile<<"[observation]"<<endl;
  char* name=new char[1000]; 
  char* hmm=new char[1000];
	for(int i=0;i<this->n_channels;i++){
	  sprintf (name, "observation_%d",i);
	  //cout<<this->data->get()->getRealValue(name)<<endl;
	  sprintf (hmm, "n%d",i+1);
	  myfile<<hmm<<" = "<<this->data->get()->getRealValue(name)<<endl;
	}
 myfile.close();
 delete [] name;
}
