#include "Onion.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include "util.h"
using namespace CryptoPP;

Onion::Onion(){
    p_det = new DET();
    p_det->recover_key_iv("key/l1_key_det", "key/det_iv");
    p_ope = new OPE();
    p_rnd = new RND();
    p_rnd->recover_keys("key/l2_key_det", "key/l2_key_ope");
}

Onion::~Onion(){
    delete p_det;
    delete p_ope;
    delete p_rnd;
}

string Onion::Encrypt(int num){
    string ct_det = p_det->Encrypt_int(num);
    
    string ct_ope = p_ope->Encrypt_int(num);
    
    string res = p_rnd->Encrypt(ct_det, ct_ope);
    
    return res;
}

string Onion::Decrypt(const string& cipher_rnd, const string& l2_key){
    return p_rnd->Decrypt(cipher_rnd, l2_key);
}
