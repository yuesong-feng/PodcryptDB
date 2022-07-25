#include "OPE.h"
#include "sope_encode.h"
#include "util.h"
#include <algorithm>
#include "Timer.h"
OPE::OPE() { }

OPE::~OPE() { }

string OPE::Encrypt_int(const int plaintext){
    // clock_t start = clock();

    uint32_t res = sope::encode(plaintext);
    string str = std::to_string(res);
    string str_hex = tohex(str);
    string prefix;
    for(int i = 0; i < 20 - str_hex.size(); ++i){
        prefix.push_back('P');
    }
    string ret = prefix + str_hex;

    // clock_t end = clock();
  	// printf("scope: OPE Encrypt, time: %lu us\n", end - start);
    return ret;
}

int OPE::Decrypt_int(const string &ciphertext){
    // clock_t start = clock();

    string str = fromhex(ciphertext);
    uint32_t c = std::stoul(str);
    int ret = sope::decode_int(c);

    // clock_t end = clock();
  	// printf("scope: OPE Decrypt, time: %lu us\n", end - start);
    return ret;
}
