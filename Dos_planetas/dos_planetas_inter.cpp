#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;
const int N=2;
//Constantes globales
const double G=1.0;
//constantes de PERFL;
const double Zeta=0.1786178958448091e00;
const double Lambda=-0.2123418310626054e0;
const double Chi=-0.6626458266981849e-1;
const double Coeficiente1=(1-2*Lambda)/2;
const double Coeficiente2=1-2*(Chi+Lambda);
//Declaración de las clases
class Cuerpo;
class Colisionador;

//---------- Clase Cuerpo --------------


class Cuerpo{
private:
  vector3D r,rold,V,F;
  double m,R;
public:
  void Inicie(double x0,double y0, double z0, double Vx0,double Vy0,double Vz0, double m0,double R0);
  void BorreFuerza(void);
  void SumeFuerza(vector3D F0);
  void Mueva_r(double dt, double coeficiente);
  void Mueva_V(double dt, double coeficiente);
  double Getx(void){return r.x();}; //Inline
  double Gety(void){return r.y();}; //Inline
  friend class Colisionador;
};
void Cuerpo::Inicie(double x0,double y0, double z0,double Vx0,double Vy0, double Vz0, double m0,double R0){
  r.load(x0,y0,z0); V.load(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Cuerpo::BorreFuerza(void){
  F.load(0,0,0);
}
void Cuerpo::SumeFuerza(vector3D F0){
  F+=F0;
}

void Cuerpo::Mueva_r(double dt, double coeficiente){
   r+=V*(dt*coeficiente);
  
}
void Cuerpo::Mueva_V(double dt, double coeficiente){
   V+=F*(dt*coeficiente/m);
  
}
//-------Clase colisionador----------
class Colisionador{
private:
public:
void CalculeFuerzas(Cuerpo * Planeta);
void CalculeFuerzaEntre(Cuerpo & Planeta1, Cuerpo &Planeta2);
};
void Colisionador::CalculeFuerzas(Cuerpo * Planeta){
  int i, j;
  //Borrar fuerzas;
  for (i=0; i<N;i++)
  Planeta[i].BorreFuerza();
  //Calcular las fuerzas entre todas lasparejas del planeta
  for(i=0;i<N;i++)
    for (j=i+1;j<N;j++)
      CalculeFuerzaEntre(Planeta[i], Planeta[j]);
}

void Colisionador::CalculeFuerzaEntre(Cuerpo & Planeta1, Cuerpo & Planeta2){
  vector3D r21, n, F1; double d21, F;
  r21=Planeta2.r-Planeta1.r; d21=r21.norm(); n=r21/d21;
  F = G*Planeta1.m*Planeta2.m*(d21, -2.0);
  F1=F*n; Planeta1.SumeFuerza(F1); Planeta2.SumeFuerza(F1*(-1));
}
//----------- Funciones Globales -----------
int main(){
  Cuerpo Planeta[N];
  Colisionador Newton;
  double m0=1, m1=1, r=11;
  double M = m0+m1, x0=-m1*r/M, x1=m0*r/M;
  double omega = sqrt(G*M/(r*r*r)), T = 2*M_PI/omega,V0=omega*x0, V1=omega*x1;
  double t,dt=1.0;
  int i;

  //omega=sqrt(G/(r0*r0*r0)); V0=omega*r0; T=2*M_PI/omega;
  
  //------------(x0,y0,z0,Vx0,Vy0,Vz0,m0,R0)
  Planeta[0].Inicie(x0,0,0,0,V0,0,m0,0.5);
  Planeta[1].Inicie(x1,0,0,0,V1,0,m1,1.0);
  for(t=0;t<1.1*T;t+=dt){
    cout<<Planeta[i].Getx()<<" "<<Planeta[i].Gety()<<endl;
    for(i=0;i<N;i++) {Planeta[i].Mueva_r(dt,Zeta);}
    Newton.CalculeFuerzas(Planeta);
    for(i=0;i<N;i++){ Planeta[i].Mueva_V(dt,Coeficiente1);}
    for(i=0;i<N;i++) {Planeta[i].Mueva_r(dt,Chi);}
    Newton.CalculeFuerzas(Planeta);
    for(i=0;i<N;i++) {Planeta[i].Mueva_V(dt,Lambda);}
    for(i=0;i<N;i++) {Planeta[i].Mueva_r(dt,Coeficiente2);}
    Newton.CalculeFuerzas(Planeta);
    for(i=0;i<N;i++) {Planeta[i].Mueva_V(dt,Lambda);}
    for(i=0;i<N;i++) {Planeta[i].Mueva_r(dt,Chi);}
    Newton.CalculeFuerzas(Planeta);
    for(i=0;i<N;i++) {Planeta[i].Mueva_V(dt,Coeficiente1);}
    for(i=0;i<N;i++) {Planeta[i].Mueva_r(dt,Zeta);}

  }

  return 0;
}
