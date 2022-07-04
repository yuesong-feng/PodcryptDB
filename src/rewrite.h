#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

string encrypt_sql(const string &sql);

vector<vector<string>> decrypt_res(const vector<vector<string>> &res);