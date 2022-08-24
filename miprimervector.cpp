// Mi primer programa con vector.h

#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;

int main(void){
    vector3D a,b,c;

    a.load(1,0,0);//carga la instancia a de vector3d con ese valor
    b.load(0,1,0);
    //b=2*a;
    c+=(a^b);
    c.show();
    cout<<a*b<<endl;

    return 0;
}
