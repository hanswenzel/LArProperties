#include "TF1.h"
#include "TF2.h"
#include "TMath.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TText.h" 
// const 
double birks(double x)  {
  const double A   = 0.800;       // +/- 0.003
  const double K   = 0.048670;    // +/- 0.0006
  const double rho = 1.396;
  double ED = x; 
  double dEdx  = 1.8;
  double R = A/(1+(K*dEdx)/(rho*ED));
  return R;
}

double rbox(double x)  {
  const double alpha = 0.93;
  const double beta = 0.207;
  const double rho = 1.396;
  double ED = x; 
  double dEdx  = 1.8;
  double rb= TMath::Log(alpha + beta/(rho*ED) * dEdx)/( beta/(rho*ED) * dEdx);
  return rb;
}
double birks1(double x)  {
  const double A   = 0.800;       // +/- 0.003
  const double K   = 0.048670;    // +/- 0.0006
  const double rho = 1.396;
  double ED = 0.5; 
  double dEdx  = x;
  double R = A/(1+(K*dEdx)/(rho*ED));
  return R;
}

double rbox1(double x)  {
  const double alpha = 0.93;
  const double beta = 0.207;
  const double rho = 1.396;
  double ED = 0.5; 
  double dEdx  = x;
  double rb= TMath::Log(alpha + beta/(rho*ED) * dEdx)/( beta/(rho*ED) * dEdx);
  return rb;
}
double birks2D(Double_t *x,Double_t *p)  {
  const double A   = 0.800;       // +/- 0.003
  const double K   = 0.048670;    // +/- 0.0006
  const double rho = 1.396;
  Double_t R = A/(1+(K*x[1])/(rho*x[0]));
  return R;
}

double rbox2D(Double_t *x,Double_t *p)  {
  const double alpha = 0.93;
  const double beta = 0.207;
  const double rho = 1.396;
  double rb= TMath::Log(alpha + beta/(rho*x[0]) * x[1])/( beta/(rho*x[0]) * x[1]);
  return rb;
}


void recom()
{
 TCanvas *canvas = new TCanvas("canvas", "recombination factors", 200, 10, 1000, 800);
 canvas->SetGrid();
 TF1 *bi  = new TF1("birks","birks(x)",0,1.);
 bi->SetNpx(500);
 bi->SetLineWidth(4);
 bi->SetLineColor(4);
 bi->GetXaxis()->SetTitle("E_{D} [kV/cm]");
 bi->GetYaxis()->SetTitle("R= Q/Q_{0}");
 bi->SetMinimum(0.);
 bi->SetTitle("");
 bi->SetMaximum(1.);
 bi->Draw(); 
 TF1 *frbox  = new TF1("rbox","rbox(x)",0,1.);
 frbox->SetNpx(500);
 frbox->SetLineWidth(4);
 frbox->SetLineColor(2);
 frbox->GetXaxis()->SetTitle("E_{D} [kV/cm]");
 frbox->GetYaxis()->SetTitle("R= Q/Q_{0}");
 frbox->SetMinimum(0.);
 frbox->SetTitle("");
 frbox->SetMaximum(1.);

 frbox->Draw("SAME");
 TLegend *leg = canvas->BuildLegend(.7, .15, 0.85, .35);
 leg->Draw();
 TText *t = new TText(.1,.1,"dE/dx=1.8 MeV/cm");
 //t->SetTextAlign(22);
 //t->SetTextColor(kRed+2);
 t->SetTextFont(43);
 t->SetTextSize(40);
 t->Draw();
}

void recom1()
{
 TCanvas *canvas1 = new TCanvas("canvas1", "recombination factors", 200, 10, 1000, 800);
 canvas1->SetGrid();
 TF1 *bi1  = new TF1("birks1","birks1(x)",0,10.);
 bi1->SetNpx(500);
 bi1->SetLineWidth(4);
 bi1->SetLineColor(4);
 bi1->GetXaxis()->SetTitle("dE/dx [MeV/cm]");
 bi1->GetYaxis()->SetTitle("R= Q/Q_{0}");
 bi1->SetMinimum(0.);
 bi1->SetTitle("");
 bi1->SetMaximum(1.);
 bi1->Draw(); 
 TF1 *frbox1  = new TF1("rbox1","rbox1(x)",0,10.);
 frbox1->SetNpx(500);
 frbox1->SetLineWidth(4);
 frbox1->SetLineColor(2);
 frbox1->GetXaxis()->SetTitle("dE/dx [MeV/cm]");
 frbox1->GetYaxis()->SetTitle("R= Q/Q_{0}");
 frbox1->SetMinimum(0.);
 frbox1->SetTitle("");
 frbox1->SetMaximum(1.);

 frbox1->Draw("SAME");
 TLegend *leg = canvas1->BuildLegend(.7, .15, 0.85, .35);
 leg->Draw();
 TText *t = new TText(1,.1,"ED =0.5 kV/cm");
 //t->SetTextAlign(22);
 //t->SetTextColor(kRed+2);
 t->SetTextFont(43);
 t->SetTextSize(40);
 t->Draw();
}
void recom2D()
{
 TCanvas *canvas3 = new TCanvas("canvas3", "recombination factors", 200, 10, 1000, 800);
 //canvas3->SetGrid();
 TF2 *bi2D  = new TF2("birks2D",birks2D,0,1.,0,10.);
 
 //bi2D->SetNpx(500);
 
 // bi2D->SetLineWidth(4);
 //bi2D->SetLineColor(4);
 bi2D->GetXaxis()->SetTitle("EDrift [kV/cm]");
 bi2D->GetXaxis()->SetTitleOffset(1.6);
 bi2D->GetYaxis()->SetTitle("dE/dx [MeV/cm]");
 //bi2D->SetMinimum(0.);
 bi2D->SetTitle("");
  bi2D->SetMaximum(0.);
 bi2D->SetMaximum(1.);
 bi2D->Draw("surf1"); 
 /* TF1 *frbox1  = new TF1("rbox1","rbox1(x)",0,10.);
 frbox1->SetNpx(500);
 frbox1->SetLineWidth(4);
 frbox1->SetLineColor(2);
 frbox1->GetXaxis()->SetTitle("dE/dx [MeV/cm]");
 frbox1->GetYaxis()->SetTitle("R= Q/Q_{0}");
 frbox1->SetMinimum(0.);
 frbox1->SetTitle("");
 frbox1->SetMaximum(1.);

 frbox1->Draw("SAME");
 */
 TLegend *leg = canvas3->BuildLegend(.7, .3, 0.85, .4);
 leg->Draw();
 
 //TText *t = new TText(1,.1,"ED =0.5 kV/cm");
 //t->SetTextAlign(22);
 //t->SetTextColor(kRed+2);
 //t->SetTextFont(43);
 //t->SetTextSize(40);
 //t->Draw();

}
void box2D()
{
 TCanvas *canvas4 = new TCanvas("canvas4", "recombination factors", 200, 10, 1000, 800);
 //canvas3->SetGrid();
 TF2 *box2D  = new TF2("rbox2D",rbox2D,0,1.,0,10.);
 
 //box2D->SetNpx(500);
 
 // box2D->SetLineWidth(4);
 //box2D->SetLineColor(4);
 box2D->GetXaxis()->SetTitle("EDrift [kV/cm]");
 box2D->GetXaxis()->SetTitleOffset(1.6);
 box2D->GetYaxis()->SetTitle("dE/dx [MeV/cm]");
 box2D->SetMinimum(0.);
 box2D->SetTitle("");
 box2D->SetMaximum(1.);
 box2D->Draw("surf1"); 
 /* TF1 *frbox1  = new TF1("rbox1","rbox1(x)",0,10.);
 frbox1->SetNpx(500);
 frbox1->SetLineWidth(4);
 frbox1->SetLineColor(2);
 frbox1->GetXaxis()->SetTitle("dE/dx [MeV/cm]");
 frbox1->GetYaxis()->SetTitle("R= Q/Q_{0}");
 frbox1->SetMinimum(0.);
 frbox1->SetTitle("");
 frbox1->SetMaximum(1.);

 frbox1->Draw("SAME");
 */
 TLegend *leg = canvas4->BuildLegend(.7, .3, 0.85, .4);
 leg->Draw();
 
 //TText *t = new TText(1,.1,"ED =0.5 kV/cm");
 //t->SetTextAlign(22);
 //t->SetTextColor(kRed+2);
 //t->SetTextFont(43);
 //t->SetTextSize(40);
 //t->Draw();

}
