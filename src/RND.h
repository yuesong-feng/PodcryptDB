#pragma once
#include <string>
#include <vector>
using namespace std;

class RND{
public:
    vector<string> keys;
    RND();
    ~RND();
    string Encrypt(const string &str1, const string &str2);
    string Decrypt(const string &cipher, const string &key);
    void store_keys(const char* l2_det_path, const char* l2_ope_path);
    void recover_keys(const char* l2_det_path, const char* l2_ope_path);
    vector<string> generate_key(int size1, int size2, int cut1 = 3, int cut2 = 3);
    vector<pair<int, int>> key_to_pairs(const string &key);
};
