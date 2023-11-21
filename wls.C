#include "TF1.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include "TAxis.h"
#include <cmath>
#include <iostream>
const double c = 299792458.;         // speed of light in m/sec
const double h = 4.13566743E-15;     // Planck constant in eVsec
double lambdatoe(double lambda) {
    // input   photon wavelength in nm 
    // return  energy in eV
    double E = (h * c) / (lambda * 1.e-9);
    return E;
}

double etolambda(double E) {
    // input  photon energy in eV
    // return   wavelength in nm 
    double lambda = (h * c) / (E * 1.e-9);
    return lambda;
}


// Data from: 
// Eur. Phys. J. C (2018) 78:329
//

Double_t myfunction(Double_t *x, Double_t *par) {
    Float_t xx = x[0];
    double f = 0.5 * par[0] * par[1] * exp(0.5 * par[1]*(2. * par[3] + par[1] * par[2] * par[2] - 2 * xx)) * TMath::Erfc((par[3] + par[1] * par[2] * par[2] - xx) / (sqrt(2) * par[2]))
      +( (1 - par[0]) / sqrt(2. * par[4] * par[4] * M_PI)) * exp((-1.0 * (xx - par[5])*(xx - par[5])) / (2. * par[4] * par[4]));
    f= f*par[6];
    return f;
}

void wls() {
    double A = 1;
    double alpha = 3.7e-2;
    double sig1 = 15.43;
    double mu1 = 418.1;
    double sig2 = 9.72;
    double mu2 = 411.2;
    double Const = 10;
    TCanvas *c1 = new TCanvas("c1","Emission spectrum",200,10,700,500);
    c1->SetGridx();
    c1->SetGridy();

    TGraph* tg1 = new TGraph("FitReemissionSpect.csv", "%lf,%lf");
    tg1->SetLineWidth(2);
    tg1->SetLineColor(2);
    tg1->GetXaxis()->SetTitle("#lambda [nm]");
    tg1->GetYaxis()->SetTitle("Quantum efficiency Qeff");
    tg1->SetMinimum(0.);
    tg1->Draw();
    cout <<tg1->Eval(420)<<endl;
    
    TF1 *f1 = new TF1("myfunc", myfunction, 370., 560., 7);
    f1->SetLineColor(4);
    f1->SetParameters(A, alpha, sig1, mu1, sig2, mu1,Const);
    f1->SetParNames("A", "alpha", "sig1", "mu1", "sig2", "mu2","Const");
    //f1->Draw("SAME");
    tg1->Fit("myfunc");
    f1->Draw("SAME");
    c1->Update();
}
//----------------------------------------------------------------------
// function prints out the WLS emmission spectrum  in the geant 4 gdml format
// emin and emax in nm
// nsteps number of steps
// index of Temperature Array
//----------------------------------------------------------------------

void wlstable(double emin = 370, double emax = 560, int nsteps = 100) {
    const double minlambda = 360;
    const double maxlambda = 570;
    if (emin < minlambda || emax > maxlambda) {
        cout << " variables out of range: " << minlambda << " - " << maxlambda << endl;
        return;
    }
    TGraph* tg1 = new TGraph("FitReemissionSpect.csv", "%lf,%lf");		 
    double stepsize = (emax - emin) / nsteps;
    double pe = emax;
    double photone = lambdatoe(pe);
    cout << "     <matrix name=\"EMISSION\" coldim=\"2\" values=\"" << endl;
    for (int i = 1; i < nsteps; i++) {
        pe = emax - i*stepsize;
        photone = lambdatoe(pe);     // Photon energy in eV
	tg1->Eval(pe);
        cout << photone << "*eV "<<tg1->Eval(pe) << endl;
    }  
    cout <<  "\"/>" << endl;
}
