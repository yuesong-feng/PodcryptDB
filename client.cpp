#include <iostream>
#include <string>

#include "src/proxy.h"
using namespace std;
void show_result(vector<vector<string>> &a);

int main() {
  string sql;
  while (true) {
    cout << "------------START-------------" << endl;
    cout << "1. insert into numtest values(num1, num2);\n";
    cout << "2. select * from numtest;\n";
    cout << "3. select * from numtest where field = num\n";
    cout << "4. select * from numtest where field between num1 and num2\n";
    cout << "5. select sum(*) from numtest;\n";

    cout << "input operation: ";
    int op;
    cin >> op;
    if (op == 1) {
      cout << "input num1, num2: ";
      int num1, num2;
      cin >> num1 >> num2;
      sql = "insert into numtest values (" + to_string(num1) + ", " +
            to_string(num2) + ");";
      proxy_insert_numtest(num1, num2);
    } else if (op == 2) {
      auto res = proxy_select_numtest();
      show_result(res);
    } else if (op == 3) {
      cout << "input field, num: ";
      string field;
      int num;
      cin >> field >> num;
      auto res = proxy_select_numtest_equal(field, num);
      show_result(res);
    } else if (op == 4) {
      cout << "input field, num1, num2: ";
      string field;
      int num1, num2;
      cin >> field >> num1 >> num2;
      auto res = proxy_select_numtest_between(field, num1, num2);
      show_result(res);
    } else if(op == 5){
        auto res = proxy_select_numtest_sum();
        show_result(res);
    }
  }
  return 0;
}

void show_result(vector<vector<string>> &a) {
  for (auto &row : a) {
    for (auto &col : row) {
      cout << "| " << col << " ";
    }
    cout << "|" << endl;
  }
  cout << "------------" << endl;
}