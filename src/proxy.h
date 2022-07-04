#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<vector<string>> proxy(const string &sql);

bool proxy_insert_numtest(int num1, int num2);

vector<vector<string>> proxy_select_numtest_equal(const string& field, int num);

vector<vector<string>> proxy_select_numtest();

vector<vector<string>> proxy_select_numtest_between(const string& field, int num1, int num2);

vector<vector<string>> proxy_select_numtest_sum();
