#pragma once
#include <string>
#include "cryptopp/config_int.h"
#include "cryptopp/secblock.h"
using namespace CryptoPP;
using namespace std;

class DET{
public:
    SecByteBlock *key;
    byte *iv;

    DET();
    ~DET();
    string Encrypt_int(const int plaintext);
    int Decrypt_int(const string &ciphertext);
    string Encrypt(const string &plaintext);
    string Decrypt(const string &ciphertext);
    void GenerateKey();
    void SetKey(SecByteBlock *key, byte *iv);
    void print_key();
    void print_iv();
    void store_key_iv(const string &key_path, const string &iv_path);
    void recover_key_iv(const string &key_path, const string &iv_path);
};
