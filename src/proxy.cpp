#include "proxy.h"
#include <iostream>
#include <pg_query.h>

#include "rewrite.h"
#include "server.h"
#include "util.h"
#include "Onion.h"
using namespace std;

bool proxy_insert_numtest(int num1, int num2){
  // clock_t start = clock();
  cout << "original sql: " << "INSERT INTO numtest VALUES (" << num1 << ", " << num2 << ");" << endl;
  
  Onion o;
  string rewrote_sql = "INSERT INTO numtest VALUES ('" + o.Encrypt(num1) + "', '" + o.Encrypt(num2) + "');";

  cout << "proxy encrypt to: " << rewrote_sql << endl;
  auto server_ret = server_insert_numtest(rewrote_sql);
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return true;
}

vector<vector<string>> proxy_select_numtest_equal(const string& field, int num){
  // clock_t start = clock();
  DET det;
  det.recover_key_iv("key/l1_key_det", "key/det_iv");
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  // string original_sql = "SELECT * FROM numtest where " + field + "=" + to_string(num) + ";";
  // cout << original_sql << endl;

  string encrypted = det.Encrypt_int(num);
  // string sql = "SELECT * FROM numtest where " + field + "=" + encrypted + ";";
  // cout << sql << endl;
  vector<vector<string>> server_ret = server_select_numtest_equal(field, encrypted);

  for (int i = 1; i < server_ret.size(); ++i) {
    vector<string> &row = server_ret[i];
    for (string &col : row) {
      string cipher_det = rnd.Decrypt(col, rnd.keys[0]);
      int plain = det.Decrypt_int(cipher_det);
      col = to_string(plain);
    }
  }
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return server_ret;
}

vector<vector<string>> proxy_select_numtest(){
  // clock_t start = clock();

  DET det;
  det.recover_key_iv("key/l1_key_det", "key/det_iv");
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  string sql = "SELECT * FROM numtest;";
  cout << sql << endl;
  vector<vector<string>> server_ret = server_select_numtest();

  for (int i = 1; i < server_ret.size(); ++i) {
    vector<string> &row = server_ret[i];
    for (string &col : row) {
      string cipher_det = rnd.Decrypt(col, rnd.keys[0]);
      int plain = det.Decrypt_int(cipher_det);
      col = to_string(plain);
    }
  }

	// clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return server_ret;
}

vector<vector<string>> proxy_select_numtest_between(const string& field, int num1, int num2){
  // clock_t start = clock();
  OPE ope;
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  string original_sql = "SELECT * FROM numtest where " + field + " BETWEEN " + to_string(num1) + " AND " + to_string(num2) + ";";
  cout << original_sql << endl;

  string encrypted1 = ope.Encrypt_int(num1);
  string encrypted2 = ope.Encrypt_int(num2);
  string sql = "SELECT * FROM numtest where " + field + " BETWEEN " + encrypted1 + " AND " + encrypted2 + ";";
  cout << sql << endl;
  vector<vector<string>> server_ret = server_select_numtest_between(field, encrypted1, encrypted2);

  for (int i = 1; i < server_ret.size(); ++i) {
    vector<string> &row = server_ret[i];
    for (string &col : row) {
      string cipher_det = rnd.Decrypt(col, rnd.keys[1]);
      int plain = ope.Decrypt_int(cipher_det);
      col = to_string(plain);
    }
  }
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return server_ret;
}

vector<vector<string>> proxy_select_numtest_sum(){
  // clock_t start = clock();
  auto tmp = proxy_select_numtest();
  vector<vector<string>> res;
  res.push_back(tmp.front());
  vector<string> sum_vec(tmp[0].size(), "");
  for(int col = 0; col < sum_vec.size(); ++col){
    int sum_num = 0;
    for(int row = 1; row < tmp.size(); ++row){
      sum_num += stoi(tmp[row][col]);
    }
    sum_vec[col] = to_string(sum_num);
  }
  res.push_back(sum_vec);
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return res;
}

bool proxy_delete_numtest_equal(const string& field, int num){
  // clock_t start = clock();
  cout << "original sql: " << "DELETE FROM numtest WHERE " << field << " = " << num << ";" << endl;

  Onion o;
  string rewrote_sql = "DELETE FROM numtest WHERE " + field + " = '" + o.Encrypt(num) + "';";

  cout << "proxy encrypt to: " << rewrote_sql << endl;
  auto server_ret = server_delete_numtest_equal(rewrote_sql);
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return true;
}

bool proxy_delete_numtest_between(const string& field, int num1, int num2){
  // clock_t start = clock();
  OPE ope;
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  string original_sql = "DELETE FROM numtest where " + field + " BETWEEN " + to_string(num1) + " AND " + to_string(num2) + ";";
  cout << original_sql << endl;
  
  string ct1 = ope.Encrypt_int(num1);
  string ct2 = ope.Encrypt_int(num2);
  string sql = "DELETE FROM numtest where " + field + " BETWEEN " + ct1 + " AND " + ct2 + ";";
  cout << sql << endl;
  vector<vector<string>> server_ret = server_delete_numtest_between(field, ct1, ct2);
  // clock_t end = clock();
  // printf("scope: Proxy, time: %lu us\n", end - start);
  return true;
}