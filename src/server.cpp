#include "server.h"
#include <iostream>
#include <vector>
#include <pqxx/pqxx>
#include <string.h>
#include "util.h"
#include "RND.h"
using namespace std;

vector<vector<string>> server_insert_numtest(const string &sql) {
  try {
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec(sql)};
    txn.commit();
    return {};
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}

vector<vector<string>> server_select_numtest_equal(const string &field, const string& val) {
  try {
    RND rnd;
    rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec("SELECT * FROM numtest;")};
    txn.commit();
  
    vector<vector<string>> vec;
    vector<string> first_row;
    for(auto rol : result[0]){
      first_row.push_back(rol.name());
    }
    vec.push_back(first_row);
    for (auto row : result) {
      bool match = false;
      vector<string> row_vec;
      for(auto col : row){
        string content = col.c_str();
        row_vec.push_back(content);

        string field_name(col.name());
        if(field_name == field){
          if(val == rnd.Decrypt(content, rnd.keys[0])){
            match = true;
          }
        }
      }
      if(match){
        vec.push_back(row_vec);
      }
    }
    return vec;
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}

vector<vector<string>> server_select_numtest(){
  try {
    RND rnd;
    rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec("SELECT * FROM numtest;")};
    txn.commit();
  
    vector<vector<string>> vec;
    vector<string> first_row;
    for(auto rol : result[0]){
      first_row.push_back(rol.name());
    }
    vec.push_back(first_row);

    for (auto row : result) {
      vector<string> row_vec;
      for(auto col : row){
        string content = col.c_str();
        row_vec.push_back(content);
      }
      vec.push_back(row_vec);
    }
    return vec;
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}

vector<vector<string>> server_select_numtest_between(const string& field, const string& val1, const string& val2){
  try {
    RND rnd;
    rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec("SELECT * FROM numtest;")};
    txn.commit();
  
    vector<vector<string>> vec;
    vector<string> first_row;
    for(auto rol : result[0]){
      first_row.push_back(rol.name());
    }
    vec.push_back(first_row);
    
    for (auto row : result) {
      bool match = false;
      vector<string> row_vec;
      for(auto col : row){
        string content = col.c_str();
        row_vec.push_back(content);

        string field_name(col.name());
        if(field_name == field){
          EncodedTuple low(fromhex(val1));
          EncodedTuple high(fromhex(val2));
          EncodedTuple value(fromhex(rnd.Decrypt(content, rnd.keys[1])));
          int r1 = compTuple(low, value);
          int r2 = compTuple(value, high);
          if((r1 == -1 || r1 == 0) && (r2 == -1 || r2 == 0)){
            match = true;
          }
        }
      }
      if(match){
        vec.push_back(row_vec);
      }
    }
    return vec;
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}

vector<vector<string>> server_delete_numtest_equal(const string &sql){
    try {
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec(sql)};
    txn.commit();
    return {};
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}

vector<vector<string>> server_delete_numtest_between(const string& field, const string& val1, const string& val2){
    try {
    RND rnd;
    rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");
    pqxx::connection c{
        "dbname=testdb user=postgres password=postgres \
        hostaddr=127.0.0.1 port=5432"};

    pqxx::work txn{c};
    pqxx::result result{txn.exec("SELECT * FROM numtest;")};
    txn.commit();
      
    for (auto row : result) {
      bool match = false;
      for(auto col : row){
        string content = col.c_str();
        string field_name(col.name());
        if(field_name == field){
          EncodedTuple low(fromhex(val1));
          EncodedTuple high(fromhex(val2));
          EncodedTuple value(fromhex(rnd.Decrypt(content, rnd.keys[1])));
          int r1 = compTuple(low, value);
          int r2 = compTuple(value, high);
          if((r1 == -1 || r1 == 0) && (r2 == -1 || r2 == 0)){
                string del_sql = "DELETE FROM numtest WHERE " + field + " = '" + content + "';";
                pqxx::work delete_txn{c};
                pqxx::result delete_res{delete_txn.exec(del_sql)};
                delete_txn.commit();
          }
        }
      }
    }
    return {};
  } catch (pqxx::sql_error const &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return {};
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {};
  }
}