#include <iostream>
#include <cmath>
#include "vector.h"
#include "Random64.h"

using namespace std;

const double K=1.0e4;
const double Lx=60, Ly = 60;
const int Nx = 6, Ny=6, N=Nx*Ny; 

//constantes de PEFRL
const double Zeta=0.1786178958448091e00;
const double Lambda=-0.2123418310626054e0;
const double Chi=-0.6626458266981849e-1;
const double Coeficiente1=(1-2*Lambda)/2;
const double Coeficiente2=1-2*(Chi+Zeta);

//Declaración de las clases
class Cuerpo;
class Colisionador;

class Cuerpo{
private:
  vector3D r,V,F;  double m,R;
public:
  void Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0);
  void BorreFuerza(void){F.load(0,0,0);};
  void SumeFuerza(vector3D F0){F+=F0;};
  void Mueva_r(double dt,double coeficiente);
  void Mueva_V(double dt,double coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; //Inline
  double Gety(void){return r.y();}; //Inline
  double Getz(void){return r.z();}; //Inline
  friend class Colisionador;
};
void Cuerpo::Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0){
  r.load(x0,y0,z0);  V.load(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Cuerpo::Mueva_r(double dt,double coeficiente){
  r+=V*(dt*coeficiente);
}
void Cuerpo::Mueva_V(double dt,double coeficiente){
  V+=F*(dt*coeficiente/m);
}
void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}
//---------- Clase Colisionador --------------
class Colisionador{
private:
public:
  void CalculeFuerzas(Cuerpo * Molecula);
  void CalculeFuerzaEntre(Cuerpo & Molecula1,Cuerpo & Molecula2);    
};
void Colisionador::CalculeFuerzas(Cuerpo * Molecula){
  int i,j;
  //Borrar fuerzas
  for(i=0;i<N;i++)
    Molecula[i].BorreFuerza();
  //Calcular las fuerzas entre todas las parejas de Moleculas
  for(i=0;i<N;i++)
    for(j=i+1;j<N+4;j++)
      CalculeFuerzaEntre(Molecula[i],Molecula[j]);
}
void Colisionador::CalculeFuerzaEntre(Cuerpo & Molecula1,Cuerpo & Molecula2){
  vector3D r21, n,F1; double d21,s, F;
  d21=r21.norm();
  s= (Molecula2.Getx()+Molecula2.R)-(Molecula1.Getx()-Molecula1.R); n = r21/d21;
  r21=Molecula2.r-Molecula1.r;
  if (s>0){ F=K*pow(s,1.5);
    F1 = n*F;
    Molecula2.SumeFuerza(F1);
    Molecula1.SumeFuerza((-1)*F1);
 }
}
void InicieAnimacion(void){
  //  cout<<"set terminal gif animate"<<endl; 
  //  cout<<"set output 'DosMoleculas.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-10:"<<Lx+10<<"]"<<endl;
  cout<<"set yrange[-10:"<<Ly+10<<"]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
    cout<<" , "<<Lx/7<<"*t,0"; //pared de abajo
    cout<<" , "<<Lx/7<<"*t,"<<Ly; //pared de arriba
    cout<<" , 0,"<<Ly/7<<"*t"; //pared de izquierda
    cout<<" , "<<Lx<<","<<Ly/7<<"*t";
}
void TermineCuadro(void){
    cout<<endl;
}


int main(){
  Cuerpo Molecula[N+4];
  Colisionador Hertz;
  Crandom ran64(1);
  double m0=1, R0=2, kT=10, V0=sqrt(2*kT/m0);
  int i, ix, iy;
  double t, tdibujo, tmax=10*(Lx/V0),tcuadro=tmax/1000, dt = 0.001;
  double dx=Lx/(Nx+1), dy = Ly/(Ny+1);
  double Theta;

  InicieAnimacion(); //dibujar

//Inicializar las paredes
double Rpared = 100*Lx, Mpared = 100*m0;

  //---------------(x0,y0,z0,Vx0,    Vy0,Vz,m0,R0)
  Molecula[N+0].Inicie(Lx/2, Ly+Rpared, 0,  0, 0,0,Mpared, Rpared); //arriba
  Molecula[N+1].Inicie(Lx/2, -Rpared, 0,  0, 0,0,Mpared, Rpared); //
  Molecula[N+2].Inicie(Lx+Rpared, Ly/2, 0,  0, 0,0,Mpared, Rpared);
  Molecula[N+3].Inicie(-Rpared, Ly/2, 0,  0, 0,0,Mpared, Rpared);
  
  for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=dt){
    //Dibujar
    if(tdibujo>tcuadro){
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();
      tdibujo=0;
    }         
    
    //cout<<Molecula[1].Getx()<<" "<<Molecula[1].Gety()<<endl;
    // Mover por PEFRL
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zeta);
    Newton.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Chi);
    Newton.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Coeficiente2);
    Newton.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Chi);
    Newton.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zeta);   
  }
  
  return 0;
}

