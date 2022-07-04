#pragma once
#include <string>
using std::string;

class OPE {
public:
    OPE();
    ~OPE();
    string Encrypt_int(const int plaintext);
    int Decrypt_int(const string &ciphertext);
};

