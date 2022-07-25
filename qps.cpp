#include <iostream>
#include "ThreadPool.h"
#include "proxy.h"
using namespace std;
void func(){
    ThreadPool tp(8);

    for(int i = 0; i < 100; ++i){
        tp.Add(proxy_select_numtest_equal, "id", 1000);
    }
}
int main(){
    clock_t start = clock();
    func();
    clock_t end = clock();
    
    printf("qps, time: %lu us\n", end - start);
    return 0;
}