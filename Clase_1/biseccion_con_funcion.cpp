#include <iostream>
#include <cmath>


double f( double x){
    return sin(x)/x;
}

const double ErrMax=1e-7;
double CerosPorBiseccion (double a, double b){
double x, m,fa, fm;
    fa = f(a);
    while((b-a)>ErrMax){
        m = (a+b)/2; fm=f(m);
        if (fa*fm>0)
            {a=m; fa=fm;} //correr a hasta m;
        else
            b=m; //correr b hasta m;
    }
    return (a+b)/2;
}


int main(){
    double a=2, b=4;
         
    std::cout<<"El cero es "<<CerosPorBiseccion(a,b)<<std::endl;

    return 0;
}