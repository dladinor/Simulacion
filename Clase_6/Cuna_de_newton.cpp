#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;

//Constantes globales
const double g=980; //unidades cgs
const int N=1;

//constantes de PERFL;
const double Zeta=0.1786178958448091e00;
const double Lambda=-0.2123418310626054e0;
const double Chi=-0.6626458266981849e-1;
const double Coeficiente1=(1-2*Lambda)/2;
const double Coeficiente2=1-2*(Chi+Zeta);

//---------- Clase Cuerpo --------------
class Cuerpo{
private:
  //vector3D r,V,F;
  double theta,omega,tau;
  double m,R,l,x0, I;
public:
  void Inicie(double theta0, double omega0, double m0, double R0, double l0, double x00);
  void BorreTorque(void){tau=0;}; //Inline
  void SumeTorque(double tau0){tau+=tau0;}; //Inline
  void Mueva_theta(double dt, double coeficiente);
  void Mueva_omega(double dt, double coeficiente);
  void Dibujese(void);
  double Getx(void){return x0+l*sin(theta);}; //Inline
  double Gety(void){return -l*cos(theta);}; //Inline
  double Gettau(void){return tau;};//Inline

  friend class Colisionador; 
};


void Cuerpo::Inicie(double theta0,double omega0, double m0, double R0, double l0, double x00){
  theta=theta0; omega=omega0; m=m0; R=R0; l=l0; x0=x00; I = m*l*l;
}
void Cuerpo::Mueva_theta(double dt, double coeficiente){
   theta+=omega*(dt*coeficiente);
  
}
void Cuerpo::Mueva_omega(double dt, double coeficiente){
   omega+=tau*(dt*coeficiente/I);
}
void Cuerpo::Dibujese(void){
  cout<<" , "<<Getx()<<"+"<<R<<"*cos(t),"<<Gety()<<"+"<<R<<"*sin(t)";
}
//-------Clase colisionador----------
class Colisionador{
  private:
  public:
    void CalculeTorques(Cuerpo * Pendulo);
    void CalculeTorquesEntre(Cuerpo & Pendulo1, Cuerpo & Pendulo2);
};

void Colisionador::CalculeTorques(Cuerpo * Pendulo){
  int i, j; double tau0;
  //Borrar torques;
  for (i=0; i<N;i++){
    Pendulo[i].BorreTorque();
    tau0=-Pendulo[i].l*Pendulo[i].m*g*sin(Pendulo[i].theta);
    Pendulo[i].SumeTorque(tau0);
    }
  //Calcular las torques entre todas las parejas del Pendulo
//   for(i=0; i<N; i++)
//     for (j=i+1; j<N; j++)
//       CalculeTorqueEntre(Pendulo[i], Pendulo[j]);
// }
// void Colisionador::CalculeTorqueEntre(Cuerpo & Pendulo1, Cuerpo & Pendulo2){
// }
//----------- Funciones Globales -----------
}
void InicieAnimacion(void){
  // cout<<"set terminal gif animate"<<endl; 
  // cout<<"set output 'Dos_Pendulos.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-10:15]"<<endl;
  cout<<"set yrange[-18:7]"<<endl;
  cout<<"set size ratio -2"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
}
void TermineCuadro(void){
    cout<<endl;
}
int main(){
  int ii;
  double m=50, l0=12, R=2, x00= 5;
  double theta0=M_PI/4, omega0=0, T=2*M_PI*sqrt(l0/g);

  Cuerpo Pendulo[N];
  Colisionador Newton;
  double t,tmax=10*T,dt=0.00001; 
  double tdibujo, tcuadro=T/500;
  
  //omega=sqrt(G/(r0*r0*r0)); V0=omega*r0; T=2*M_PI/omega;
  
  //------------(double theta0, double omega0, double m0, double R0, double l0, double x00)
  Pendulo[0].Inicie(theta0,omega0,m,R,l0,x00);
  //Pendulo[1].Inicie(x1,0,0,0,V1,0,m1,0.5);

  InicieAnimacion();

  for(t=0, tdibujo=0;t<tmax;t+=dt,tdibujo+=dt){
    //Dibujar
    if(tdibujo>tcuadro){
      InicieCuadro();
      for(ii=0;ii<N;ii++) Pendulo[ii].Dibujese();
      TermineCuadro();
      tdibujo=0;
    }
    cout<<Pendulo[1].Getx()<<"\t"<<Pendulo[1].Gety()<<endl;
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_theta(dt,Zeta);}
    Newton.CalculeTorques(Pendulo);
    for(ii=0;ii<N;ii++){ Pendulo[ii].Mueva_omega(dt,Coeficiente1);}
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_theta(dt,Chi);}
    Newton.CalculeTorques(Pendulo);
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_omega(dt,Lambda);}
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_theta(dt,Coeficiente2);}
    Newton.CalculeTorques(Pendulo);
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_omega(dt,Lambda);}
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_theta(dt,Chi);}
    Newton.CalculeTorques(Pendulo);
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_omega(dt,Coeficiente1);}
    for(ii=0;ii<N;ii++) {Pendulo[ii].Mueva_theta(dt,Zeta);}

  }

  return 0;
}
