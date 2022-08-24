#include <iostream>
#include <cmath>
using namespace std;
//Constantes globales
const double GM = 1;
//Declaracion de las clases
class Cuerpo;
//----------Clase cuerpo-----------
class Cuerpo{
    private: 
        double x,y,Vx,Vy,Fx,Fy,m,R;
    public: 
        void Inicie(double x0,double y0,double Vx0,double Vy0, double m0, double R0);
        void CalculeFuerza(void);
        void Muevase(double dt);
        double Getx(void){return x;};//funcionInline
        double Gety(void){return y;};//Inline
};

void Cuerpo::Inicie(double x0,double y0,double Vx0,double Vy0, double m0, double R0){
    x=x0; y=y0; Vx=Vx0; Vy=Vy0; m=m0; R=R0;
}

void Cuerpo::CalculeFuerza(void){
Fx=-GM*m*x/(pow(sqrt(x*x+y*y),3)); Fy=-GM*m*y/(pow(sqrt(x*x+y*y),3));
}

void Cuerpo::Muevase(double dt){
    x+=Vx*dt;       y+=Vy*dt;
    Vx+=Fx/m*dt;    Vy+=Fy/m*dt;
}

//----------Funciones globales------------

int main(){
    Cuerpo Planeta;
    double r=100, omega, V0;
    double t,dt=0.01;

    omega = sqrt(GM/(r*r*r));
    V0 = omega*r;
    //-------------x0,y0,Vx0,Vy0,m0,R0) unidades vel m/s
    Planeta.Inicie(r,0,0,V0,1,0.15);
    for(t=0;t<1.1*2*M_PI/omega;t+=dt){
        cout<<Planeta.Getx()<<" "<<Planeta.Gety()<<endl;
        Planeta.CalculeFuerza();
        Planeta.Muevase(dt);
    }

    return 0;
}