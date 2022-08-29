#include <iostream>
#include <cmath>
const double Beta = 0.35;

const double Gamma = 0.08;

double f1(double t, double s, double i){
    return (-1)*Beta*s*i;
}

double f2(double t, double s, double i){
    return Beta*s*i-Gamma*i;
}

void RK4_Step(double & t0, double & s0, double & i0, double dt){
    double ds1, ds2, ds3, ds4;
    double di1, di2, di3, di4;
    ds1 = dt * f1(t0,s0,i0);
    ds2 = dt * f1(t0+dt/2, s0+ds1/2, i0+di1/2);
    ds3 = dt * f1(t0+dt/2, s0+ds2/2, i0+di2/2);
    ds4 = dt * f1(t0+dt, s0+ds3, i0+di3);

    di1 = dt * f2(t0,s0,i0);
    di2 = dt * f2(t0+dt/2, s0+ds1/2, i0+di1/2);
    di3 = dt * f2(t0+dt/2, s0+ds2/2, i0+di2/2);
    di4 = dt * f2(t0+dt, s0+ds3, i0+di3);


    s0 += (ds1 + 2*ds2 + 2*ds3 + ds4)/6 ; t0+= dt;
    i0 += (di1 + 2*di2 + 2*di3 + di4)/6 ;
}

int main(){
    double t, s, i,r , dt = 0.01;

    for(t=0, s=0.999, i=0.001 ; t <= 90; ){
        r=1-s-i;
        std::cout << t << "\t" << s << "\t" << i << "\t" << r << "\t" << s+r+i <<std::endl;
        RK4_Step(t, s, i, dt);
    }

    return 0;
}
