#include <iostream>
#include <cmath>
using namespace std;

const double r=1;

double f1(double Lambda, double R1, double R2){
    return (-R1/r) - Lambda*Lambda*R2;
}

double f2(double Lambda, double R1, double R2){
    return R1;
}

void RK4_Step(double & Lambda0, double & R10, double & R20, double dLambda){
    double dR11, dR21, dR31, dR41;
    double dR12, dR22, dR32, dR42;
    dR11 = dLambda * f1(Lambda0,R10,R20);                                           dR12 = dLambda * f2(Lambda0,R10,R20);
    dR21 = dLambda * f1(Lambda0+dLambda/2, R10+dR11/2, R20+dR12/2);                 dR22 = dLambda * f2(Lambda0+dLambda/2, R10+dR11/2, R20+dR12/2);
    dR31 = dLambda * f1(Lambda0+dLambda/2, R10+dR21/2, R20+dR22/2);                 dR32 = dLambda * f2(Lambda0+dLambda/2, R10+dR21/2, R20+dR22/2);
    dR41 = dLambda * f1(Lambda0+dLambda, R10+dR31, R20+dR32);                       dR42 = dLambda * f2(Lambda0+dLambda, R10+dR31, R20+dR32);
    
    Lambda0+= dLambda;
    R10 += (dR11 + 2*dR21 + 2*dR31 + dR41)/6 ; 
    R20 += (dR12 + 2*dR22 + 2*dR32 + dR42)/6 ;
    
}

int main (){
    double Lambda, R1, R2, dLambda=0.01;
    for(R2=1, R1=0, Lambda=0.1; Lambda<=15.0;){
    cout<<Lambda<<"\t"<<R2<<endl;
    RK4_Step(Lambda, R1, R2, dLambda);
    }  
}

