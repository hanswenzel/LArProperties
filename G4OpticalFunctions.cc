// C++ program to demonstrate the passing
// of functions as an object parameter
#include <functional>
#include <iostream>
#include "math.h"

using namespace std;

const double pi = 3.14159265358979323846;
const double p3times16 = 16. * pi*pi*pi;
const double kA = 6.02214129e23;     // Avogadro constant
const double kb = 1.3806488e-16;     // boltzmanm constant in cm2 g s-2 K-1
const double kT = 2.18e-10;          // isothermal compressibility in cm^2dyne^-1 where 1 dyne = 1 g·cm/s2
const double aw = 39.948;            // g/mol.
const double c = 299792458.;         // speed of light in m/sec
const double h = 4.13566743E-15;     // Planck constant in eVsec
const double lambdaUV = 106.6 * 1e-7;// LAr UV Resonance lambda (cm)
const double lambdaIR = 908.3 * 1e-7;// LAr IR Resonance lambda (cm)
const double alngth = 66.;           // LAr attenuation length in cm at 128 nm
// Liquid Argon 
// sellmeier coefficient from arXiv:1502.04213
// for different temperatures T
//

const double T[4] = {83.81, 86., 88., 90.}; // K
const double a0[4] = {1.24262, 1.23828, 1.23358, 1.26099};
const double aUV[4] = {0.268257, 0.266635, 0.266183, 0.236486};
const double aIR[4] = {0.00047342, 0.000848595, 0.000846994, 0.0022611};
const double rho[4] = {0.03549, 0.03513, 0.03481, 0.03449}; // mol/cm3
double density[4];
double kbTrhokT[4];
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

double sellmeier_LAr(double *x, double *p) {
    double la0 = p[0];
    double laUV = p[1];
    double laIR = p[2];
    //    cout <<"x[0]:  "<<x[0]<<" la0: " <<la0<<" laUV:  "<<laUV<<" laIR:  "<<laIR<< endl;
    double lambda = x[0]*1e-7; // convert from nm to cm
    double nsquare = la0
            +(laUV * lambda * lambda) / (lambda * lambda - lambdaUV * lambdaUV)
            +(laIR * lambda * lambda) / (lambda * lambda - lambdaIR * lambdaIR);
    return sqrt(nsquare);
}
double groupvelocity(double *x, double *p) {
    double la0  = p[0];
    double laUV = p[1];
    double laIR = p[2];
    double lUV  = p[3];
    double lIR  = p[4];
    //
    //    cout <<"x[0]:  "<<x[0]<<" la0: " <<la0<<" laUV:  "<<laUV<<" laIR:  "<<laIR<< endl;
    double lambda = x[0]*1e-7; // convert from nm to cm
    double nsquare = la0
      +(laUV * lambda * lambda) / (lambda * lambda - lUV * lUV)
      +(laIR * lambda * lambda) / (lambda * lambda - lIR * lIR);
    
    double vg =sqrt(nsquare)
      +lambda/sqrt(nsquare)* 
	 ( laUV*lUV*lUV*lambda/ ((lambda * lambda - lUV * lUV)*(lambda * lambda - lUV * lUV))+
	   laIR*lIR*lIR*lambda/ ((lambda * lambda - lIR * lIR)*(lambda * lambda - lIR * lIR))
	   );
	 
    return vg;
}

double sellmeierpe_LAr(double * x, double *p) {
    double la0 = p[0];
    double laUV = p[1];
    double laIR = p[2];
    double pe = x[0];
    double lambda = etolambda(pe);
    lambda = lambda * 1e-7; // convert from nm to cm
    double nsquare = la0
            + (laUV * lambda * lambda) / (lambda * lambda - lambdaUV * lambdaUV)
            +(laIR * lambda * lambda) / (lambda * lambda - lambdaIR * lambdaIR);
    double nord = sqrt(nsquare);
    return nord;
}


// Define add and multiply to
// return respective values
int add(int x, int y) { return x + y; }
int multiply(int x, int y, int params ) {
  cout <<"Params:  "<<params<<endl;
  return x * y; }
 
// Function that accepts an object of
// type std::function<> as a parameter
// as well
int invoke(int x, int y,int param,  function<int(int, int,int)> func)
{
  return func(x, y,param);
}

double invokeit(double *x, double *p,  function<double(double*, double*)> func1)
{
  return func1(x, p);
}
 
// Driver code
int main()
{
    // Pass the required function as
    // parameter using its name

    double p[3]={1.24262,0.26825,0.00047342};
    double x[1];
    x[0]=300.;
    //  cout <<"x[0]:  "<<x[0]<<" la0: " <<p[0]<<" laUV:  "<<p[1]<<" laIR:  "<<p[2]<< endl;
    cout << invokeit(x,p ,&sellmeier_LAr) << '\n';
    double par[5]={1.24262,0.26825,0.00047342,106.6 * 1e-7,908.3 * 1e-7};
    double xx[1];
    xx[0]=150.;
    cout << "group velocity:  "<<invokeit(xx,par ,&groupvelocity) << '\n';
    return 0;
}
