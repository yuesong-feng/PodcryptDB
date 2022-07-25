#include <iostream>
#include <pqxx/pqxx>
#include "ThreadPool.h"
#include "proxy.h"
using namespace std;
void func(){
    ThreadPool tp(8);
    for(int i = 0; i < 100; ++i){
        tp.Add(proxy_select_numtest_equal, "id", 1000);
    }
}
void server_select_numtest_equal() {
  try {
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec("SELECT * FROM nt WHERE age=1234;")};
    txn.commit();
  
    return;
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return;
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return;
  }
}
void raw(){
    ThreadPool tp(8);
    for(int i = 0; i < 100; ++i){
        tp.Add(server_select_numtest_equal);
    }
}
int main(){
    clock_t start = clock();
    raw();
    clock_t end = clock();
    
    printf("qps, time: %lu us\n", end - start);
    return 0;
}