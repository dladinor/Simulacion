#include <iostream>
#include <cmath>
using namespace std;

double f(double t,double x){
    return x/2;
}

void UnPasoDeEuler(double & t, double & x, double dt){
    double dx;
    dx=dt*f(t,x);
    t+=dt;   x+=dx;
}

int main(){
    double t,x; double dt=0.1;
    for(t=0,x=0; x<2;){
        cout<<t<<" "<<x<<" "<<x*x/2<<endl;
        UnPasoDeEuler(t,x,dt);
    }

}