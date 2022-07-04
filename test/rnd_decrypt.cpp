#include "RND.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    RND rnd;
    string cipher_rnd = recover_str("data/ciphertext_rnd");
    string l2_key_det = recover_str_hex("key/l2_key_det");
    string l2_key_ope = recover_str_hex("key/l2_key_ope");

    cout << "cipher_rnd: " << cipher_rnd << endl;
    cout << "l2_key_det " << l2_key_det << endl;
    cout << "l2_key_ope " << l2_key_ope << endl;

    string ct_det = rnd.Decrypt(cipher_rnd, l2_key_det);
    string ct_ope = rnd.Decrypt(cipher_rnd, l2_key_ope);

    cout << "decode det: " << ct_det << endl;
    cout << "decode ope: " << ct_ope << endl;
    return 0;
}