#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

vector<vector<string>> server_insert_numtest(const string &sql);

vector<vector<string>> server_select_numtest_equal(const string& field, const string& val);

vector<vector<string>> server_select_numtest();

vector<vector<string>> server_select_numtest_between(const string& field, const string& val1, const string& val2);