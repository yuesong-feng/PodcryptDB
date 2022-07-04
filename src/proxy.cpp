#include "proxy.h"
#include <iostream>
#include <pg_query.h>

#include "rewrite.h"
#include "server.h"
#include "util.h"
#include "Onion.h"
using namespace std;

// running in proxy,
// vector<vector<string>> proxy(const string &sql) {
//   // parse sql
//   cout << "original sql: " << sql << endl;

//   // encrypt int and string in sql statement
//   PgQueryParseResult result = pg_query_parse(sql.c_str());
//   printf("%s\n", result.parse_tree);
//   pg_query_free_parse_result(result);
  
//   string rewrote_sql = encrypt_sql(sql);
//   cout << "proxy encrypt to: " << rewrote_sql << endl;

//   // send sql to server, execute, get result
//   auto server_ret = server_insert(rewrote_sql);

//   // rewrite result, decrypt plaintext
//   auto res = decrypt_res(server_ret);
//   return res;
// }

bool proxy_insert_numtest(int num1, int num2){
  cout << "original sql: " << "INSERT INTO numtest VALUES (" << num1 << ", " << num2 << ");" << endl;
  
  Onion o;
  string rewrote_sql = "INSERT INTO numtest VALUES ('" + o.Encrypt(num1) + "', '" + o.Encrypt(num2) + "');";

  cout << "proxy encrypt to: " << rewrote_sql << endl;
  auto server_ret = server_insert_numtest(rewrote_sql);
  return true;
}

vector<vector<string>> proxy_select_numtest_equal(const string& field, int num){
  DET det;
  det.recover_key_iv("key/l1_key_det", "key/det_iv");
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  string sql = "SELECT * FROM numtest where " + field + "=" + det.Encrypt_int(num) + ";";
  cout << sql << endl;
  vector<vector<string>> server_ret = server_select_numtest_equal(field, det.Encrypt_int(num));

  for (int i = 1; i < server_ret.size(); ++i) {
    vector<string> &row = server_ret[i];
    for (string &col : row) {
      string cipher_det = rnd.Decrypt(col, rnd.keys[0]);
      int plain = det.Decrypt_int(cipher_det);
      col = to_string(plain);
    }
  }

  return server_ret;
}

vector<vector<string>> proxy_select_numtest(){
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

  return server_ret;
}

vector<vector<string>> proxy_select_numtest_between(const string& field, int num1, int num2){
  OPE ope;
  RND rnd;
  rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");

  string sql = "SELECT * FROM numtest where " + field + " BETWEEN " + ope.Encrypt_int(num1) + " AND " + ope.Encrypt_int(num2) + ";";
  cout << sql << endl;
  vector<vector<string>> server_ret = server_select_numtest_between(field, ope.Encrypt_int(num1), ope.Encrypt_int(num2));

  for (int i = 1; i < server_ret.size(); ++i) {
    vector<string> &row = server_ret[i];
    for (string &col : row) {
      string cipher_det = rnd.Decrypt(col, rnd.keys[1]);
      int plain = ope.Decrypt_int(cipher_det);
      col = to_string(plain);
    }
  }

  return server_ret;
}

vector<vector<string>> proxy_select_numtest_sum(){
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
  return res;
}