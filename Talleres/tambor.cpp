#include <iostream>
#include <cmath>
using namespace std;

const double Lambda=1;

double f1(double r, double R1, double R2){
    return (-1/r)*R1 - Lambda*Lambda*R2;
}

double f2(double R1, double R2, double r){
    return R1;
}

void RK4_Step(double & r0, double & R10, double & R20, double dr){
    double dR11, dR21, dR31, dR41;
    double dR12, dR22, dR32, dR42;
    dR11 = dr * f1(r0,R10,R20);                                      dR12 = dr * f2(r0,R10,R20);
    dR21 = dr * f1(r0+dr/2, R10+dR11/2, R20+dR12/2);                 dR22 = dr * f2(r0+dr/2, R10+dR11/2, R20+dR12/2);
    dR31 = dr * f1(r0+dr/2, R10+dR21/2, R20+dR22/2);                 dR32 = dr * f2(r0+dr/2, R10+dR21/2, R20+dR22/2);
    dR41 = dr * f1(r0+dr, R10+dR31, R20+dR32);                       dR42 = dr * f2(r0+dr, R10+dR31, R20+dR32);
 
    R10 += (dR11 + 2*dR21 + 2*dR31 + dR41)/6 ; 
    R20 += (dR12 + 2*dR22 + 2*dR32 + dR42)/6 ;
    r0+= dr;
}

int main (){
    double r, R1, R2, dr=0.01;
    for(R2=1, R1=0, r=0.01; r<10.0;){
    cout<<r<<"\t"<<R1<<"\t"<<R2<<endl;
    RK4_Step(r, R1, R2, dr);
    }  
}

