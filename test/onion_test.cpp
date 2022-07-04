#include "Onion.h"
#include "util.h"
#include <iostream>
using namespace std;

int main() {
  Onion o;
  while (1) {
    int op;
    cout << "1. encrypt\n2. decrypt\ninput: ";
    cin >> op;
    if(op == 1){
        int num;
        cout << "encrypt num: ";
        cin >> num;
        cout << o.Encrypt(num) << endl;
    } else if(op == 2){
        string cipher;
        cout << "decrypt ciphertext_rnd: ";
        cin >> cipher;
        // string l2_key_det = recover_str_hex("key/l2_key_det");
        cout << "l2_key_det: " << o.p_rnd->keys[0] << endl;
        // string l2_key_ope = recover_str_hex("key/l2_key_ope");
        cout << "l2_key_ope: " << o.p_rnd->keys[1] << endl;
        cout << "cipher_det: " << o.Decrypt(cipher, o.p_rnd->keys[0]) << endl;
        cout << "cipher_ope: " << o.Decrypt(cipher, o.p_rnd->keys[2]) << endl;
    }
  }

  return 0;
}