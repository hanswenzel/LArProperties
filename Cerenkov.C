#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 
#include <cmath>
//#include <math.h>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TFile.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
using namespace std;
const Int_t dim = 32;
const double c         = 299792458.;          // speed of light in m/sec
const double h         = 4.13566743E-15;      // Planck constant in eVsec
Double_t refindex[dim] = {
  1.3435,
  1.344,
  1.3445,
  1.345,
  1.3455,
  1.346,
  1.3465,
  1.347,
  1.3475,
  1.348,
  1.3485,
  1.3492,
  1.35,
  1.3505,
  1.351,
  1.3518,
  1.3522,
  1.353,
  1.3535,
  1.354,
  1.3545,
  1.355,
  1.3555,
  1.356,
  1.3568,
  1.3572,
  1.358,
  1.3585,
  1.359,
  1.3595,
  1.36,
  1.3608};
Double_t energy[dim] ={
  2.034,
  2.068,
  2.103,
  2.139,
  2.177,
  2.216,
  2.256,
  2.298,
  2.341,
  2.386,
  2.433,
  2.481,
  2.532,
  2.585,
  2.64,
  2.697,
  2.757,
  2.82,
  2.885,
  2.954,
  3.026,
  3.102,
  3.181,
  3.265,
  3.353,
  3.446,
  3.545,
  3.649,
  3.76,
  3.877,
  4.002,
  4.136};
Double_t wtrindex2(double lambda)
{
  const double p0 = 1.37899;
  const double p1 = -6.28931e-05;
  const double p2 = 7.1692e-09;
  const double min=  299.768;
  const double max=  609.558;
  double wrin=0.0;
  if (lambda<max&&lambda>min)
    {
      wrin = p0 + p1*lambda + p2*lambda*lambda;
    }
  
  return wrin;
}

//-------------------------------------------------------------------------------
//
// see formula 33.46 in Review of particle physics 2018
//  
//-------------------------------------------------------------------------------

Double_t ceren(Double_t *x, Double_t *par) {
    double lambda=x[0];
    double z = par[0];
    double beta = par[1];
    double n = wtrindex2(lambda);
    const double alpha = 7.2973525664E-3;
    double photons=0.0;
    double min=  299.768;
    double max=  609.558;
    if (lambda<max&&lambda>min)
      {
	photons=(1 - 1./(beta * beta * n * n)) *(2. * M_PI * alpha * z * z) / (lambda*lambda);
      }
    return photons;
}
double etolambda(double E)
{
  // input  photon energy in eV
  // return   wavelength in nm 
 double   lambda  = (h*c)/(E*1.e-9);
 return lambda;
}
Double_t wtrindex(Double_t *x, Double_t *par)
{
  double lambda=x[0];
  double p0 = par[0];
  double p1 = par[1];
  double p2 = par[2];
  const double min=  299.768;
  const double max=  609.558;
  double wrin=0.0;
  if (lambda<max&&lambda>min)
    {
      wrin = p0 + p1*lambda + p2*lambda*lambda;
    }

  return wrin;
  }

void Cerenkov() {
  double lambda[dim];
  for (int i = 0; i < dim; i++) {
    lambda[i]= etolambda(energy[i]);
  }
  cout<<"Lambda min:  "<<  lambda[dim-1] <<" Lambda max:  "  <<lambda[0]<<endl;
  TCanvas* c1 = new TCanvas("cerenkov canvas", "cerenkov", 200, 10, 700, 500);
  c1->SetGrid();
  c1->GetFrame()->SetBorderSize(12);
  //c1->SetLogx();
  c1->SetLogy();
  TF1 *f1 = new TF1("ceren", ceren, 100,700, 2);
  f1->SetTitle("Cerenkov photons;#lambda [nm];Nr of Photons");
  f1->SetParameters(1,1);
  f1->SetParNames("z", "beta");
  f1->Draw();
  
  TCanvas* c2 = new TCanvas("refindex canvas", "refindex", 200, 10, 700, 500);
  c2->SetGrid();
  c2->GetFrame()->SetBorderSize(12);
  //c2->SetLogx();
  //c2->SetLogy();
  TGraph* refindexgr = new TGraph(dim, energy, refindex);
  refindexgr->SetTitle("refraction index;photonEnergy [eV];refraction Index");
  refindexgr->SetName("refindex");
  refindexgr->SetMarkerColor(2);
  refindexgr->SetLineColor(2);
  refindexgr->SetMarkerStyle(20);
  refindexgr->SetMarkerSize(1);
  refindexgr->SetLineWidth(1);
  refindexgr->Draw("AC");
  
  TCanvas* c3 = new TCanvas("refindex canvas2", "refindex2", 200, 10, 700, 500);
  c3->SetGrid();
  c3->GetFrame()->SetBorderSize(12);
  //  c3->SetLogx();
  //c3->SetLogy();
  
  TGraph* refindexgr2 = new TGraph(dim, lambda, refindex);
  refindexgr2->SetTitle("refraction index used in Geant4;#lambda [nm];refraction Index");
  refindexgr2->SetName("refindex");
  refindexgr2->SetMarkerColor(4);
  refindexgr2->SetLineColor(4);
  refindexgr2->SetMarkerStyle(20);
  refindexgr2->SetMarkerSize(1);
  refindexgr2->SetLineWidth(1.5);
  refindexgr2->Draw("AC");
  
  //  TCanvas* c4 = new TCanvas("refindex canvas3", "refindex3", 200, 10, 700, 500);
  //c4->SetGrid();
  //c4->GetFrame()->SetBorderSize(12);
  //c3->SetLogx();
  //c3->SetLogy();
  TF1 *f2 = new TF1("index",wtrindex , 100,700,3);
  f2->SetParameters(1.37899,-6.28931e-05,7.1692e-09);
  f2->SetParNames("p0", "p1", "p2");
  f2->SetTitle("calculated refraction inex;#lambda [nm];refraction index");
  f2->SetMinimum(1.3);
  f2->SetMaximum(1.4);
  f2->Draw("SAME");
   TLegend *leg = c3->BuildLegend(.55, .55, 0.9, .85);
   leg->Draw();
}

