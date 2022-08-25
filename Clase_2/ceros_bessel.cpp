#include <iostream>
#include <cmath>

const double ErrMax=1e-7;
double f( double alpha, double x, double t){
    return cos(alpha*t -x*sin(t));
}

double  IntegralPorSimpson (double alpha, double x, double a, double b, int n){
double t,h,suma; int i;
    n*=2; h=(b-a)/n;
    suma=0;
   for(i=0;i<=n; i++){
    t=a+i*h;
    if(i==0 || i==n) //si es el primero o el ultimo
        suma+=f(alpha,x,t);
    else if(i%2==0) //si es par
        suma+=2*f(alpha,x,t);
    else //si es impar
        suma+=4*f(alpha,x,t);
    
   }
   return suma*h/3;
}

double Bessel(double alpha, double x){
    double a=0, b=M_PI; int n=50;
    return IntegralPorSimpson (alpha, x, a, b, n)/M_PI;
}

double CerosPorBiseccion (double alpha, double a, double b){
double x, m,fa, fm;
    fa = Bessel(alpha,a);
    while((b-a)>ErrMax){
        m = (a+b)/2; fm=Bessel(alpha, m);
        if (fa*fm>0)
            {a=m; fa=fm;} //correr a hasta m;
        else
            b=m; //correr b hasta m;
    }
    return (a+b)/2;
}


int main(){
    double alpha=0;
    double a=2, b=4;
        std::cout<<"La funcion de Bessel con alpha = "<<alpha<<". Tiene un cero en x ="<<CerosPorBiseccion(alpha, a, b)<<std::endl;   
        
    

    return 0;
}