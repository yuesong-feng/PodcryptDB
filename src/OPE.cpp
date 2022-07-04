#include "OPE.h"
#include "sope_encode.h"
#include "util.h"
#include <algorithm>
OPE::OPE() { }

OPE::~OPE() { }

string OPE::Encrypt_int(const int plaintext){
    uint32_t res = sope::encode(plaintext);
    string str = std::to_string(res);
    string str_hex = tohex(str);
    string prefix;
    for(int i = 0; i < 20 - str_hex.size(); ++i){
        prefix.push_back('P');
    }
    string ret = prefix + str_hex;
    return ret;
}

int OPE::Decrypt_int(const string &ciphertext){
    string str = fromhex(ciphertext);
    uint32_t c = std::stoul(str);
    return sope::decode_int(c);
}
