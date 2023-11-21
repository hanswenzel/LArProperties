#include <math.h> 
#include <TGraph.h> 
#include <TMultiGraph.h> 
#include <TLegend.h> 
#include <TCanvas.h> 

void speed()
{   
  TCanvas *canvas = new TCanvas("canvas", "velocities", 200, 10, 1000, 800);
  const Int_t n1= 6;
  const Int_t n2= 61;
  Double_t E[n1]= {2.0,2.5,3.0,3.5,4.0,4.5};
  Double_t t[n1]= {0.619201,0.641767,0.68141,0.73818,0.789297,0.801313};
  Double_t veff[n1];
  Double_t neff[n1];
  Double_t dnde[n2-2];
  Double_t E3[n2-2];
  Double_t vg[n2-2];
  Double_t vp[n2];
  Double_t E2[n2]={1.56258,
		   1.59515,
		   1.63606,
		   1.67667,
		   1.71167,
		   1.76698,
		   1.80023,
		   1.84655,
		   1.9016, 
		   1.95004,
		   1.99407,
		   2.03291,
		   2.07329,
		   2.12313,
		   2.155,  
		   2.20466,
		   2.25223,
		   2.30652,
		   2.36837,
		   2.43363,
		   2.48095,
		   2.54136,
		   2.58717,
		   2.65907,
		   2.73508,
		   2.80182,
		   2.85761,
		   2.93054,
		   2.99162,
		   3.04721,
		   3.0799, 
		   3.1133, 
		   3.16479,
		   3.20902,
		   3.25449,
		   3.30128,
		   3.34944,
		   3.39901,
		   3.43974,
		   3.49205,
		   3.53505,
		   3.57914,
		   3.6358, 
		   3.68244,
		   3.7303, 
		   3.79189,
		   3.84266,
		   3.90805,
		   3.94837,
		   3.97571,
		   4.04576,
		   4.07447,
		   4.14807,
		   4.19353,
		   4.25569,
		   4.33605,
		   4.43657,
		   4.50622,
		   4.63351,
		   4.76822,
		   4.86931};
  Double_t n[n2]={ 1.74822,
		   1.74941,
		   1.75,
		   1.75178,
		   1.75296,
		   1.75474,
		   1.75593,
		   1.7583,
		   1.7583,
		   1.76067,
		   1.76244,
		   1.76422,
		   1.76422,
		   1.766,
		   1.76778,
		   1.76955,
		   1.77192,
		   1.7737,
		   1.77666,
		   1.77903,
		   1.78081,
		   1.78437,
		   1.78614,
		   1.78911,
		   1.79266,
		   1.79563,
		   1.79977,
		   1.80451,
		   1.80925,
		   1.8134,
		   1.81696,
		   1.82051,
		   1.82525,
		   1.83059,
		   1.83533,
		   1.84007,
		   1.8454,
		   1.85192,
		   1.85725,
		   1.86258,
		   1.86673,
		   1.87206,
		   1.87799,
		   1.8851,
		   1.89102,
		   1.89873,
		   1.90465,
		   1.90999,
		   1.91473,
		   1.92065,
		   1.92658,
		   1.93191,
		   1.93665,
		   1.94198,
		   1.94672,
		   1.95206,
		   1.95798,
		   1.96628,
		   1.9722,
		   1.97694,
		   1.98109};
  
  const Double_t c = 2.9979e8;
  const Double_t l = 0.1;
  for (int i=0;i<n1;i++)
    {
      neff[i]=(c*t[i]*1e-9)/l;
      veff[i]= 1./neff[i];
    }
  for (int i=0;i<n2;i++)
    {
      vp[i]=1./n[i];
    }
    for (int jj=1;jj<n2-1;jj++)
    {
      dnde[jj-1]=   (n[jj+1]-n[jj-1])/(log(E2[jj+1])-log(E2[jj-1]));
      E3[jj-1] =    0.5*(E2[jj+1]+E2[jj-1]);
      vg[jj-1] =    1./(n[jj]+dnde[jj-1]);
      
    } 
    
  TGraph *gr = new TGraph(n1,E,t);
  TGraph *ne = new TGraph(n1,E,neff);
  TGraph *ng = new TGraph(n2,E2,n);
  TGraph *ve = new TGraph(n1,E,veff);
  TGraph *vphase = new TGraph(n2,E2,vp);
  TGraph *vgroup = new TGraph(n2-2,E3,vg);

  vphase->SetLineColor(2);
  vphase->SetMarkerColor(2);
  vphase->SetMarkerStyle(2);
  vphase->SetTitle("phase velocity");
  ve->SetLineColor(3);
  ve->SetMarkerColor(3);
  ve->SetMarkerStyle(3);
  ve->SetTitle("geant 4 velocity");
  vgroup->SetLineColor(4);
  vgroup->SetMarkerColor(4);
  vgroup->SetMarkerStyle(4);
  vgroup->SetTitle("group velocity");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(vphase);
  mg->Add(ve);
  mg->Add(vgroup);
  mg->SetTitle("material PbF4;Photon energy [eV]; velocity/c");
  mg->SetMinimum(0.4);
  mg->SetMaximum(0.6);
  mg->Draw("apl");
  TLegend *leg = canvas->BuildLegend(.6, .65, 0.85, .85);
  leg->Draw();
}
