#include "src/proxy.h"
#include <iostream>
using namespace std;

int main(){
    srand((int)time(NULL));
    
    for (int i = 0; i < 500; i++)
    {
        int a =  rand() % 65535;
        int b = rand() % 65535;
        proxy_insert_numtest(a, b);
    }
    return 0;
}