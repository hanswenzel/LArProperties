// const 
double birks(double ED) {
  double A   = 0.800;       // +/- 0.003
  double K   = 0.048670;      // +/- 0.0006
  double rho = 1.396; 
  double dEdx  = 1.8;
  double R = A/(1+(K*dEdx))/(rho*ED);
  return R;
}
