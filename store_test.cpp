#include "DET.h"
#include "OPE.h"
#include "RND.h"
#include "util.h"
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
  int num;
  while (1) {
    cout << "-------------START----------" << endl;
    cout << "input num: ";
    cin >> num;
    DET det;
    det.recover_key_iv("key/l1_key_det", "key/det_iv");
    string cipher_det = det.Encrypt_int(num);
    cout << "cipher_det: " << cipher_det << endl;
    store_str(cipher_det, "data/cipher_det");
    cout << "decrypt cipher_det to plaintext: " << det.Decrypt_int(cipher_det) << endl << endl;

    OPE ope;
    string cipher_ope = ope.Encrypt_int(num);
    cout << "cipher_ope: " << cipher_ope << endl;
    store_str(cipher_ope, "data/cipher_ope");
    cout << "decrypt cipher_ope to plaintext: " << ope.Decrypt_int(cipher_ope) << endl << endl;

    RND rnd;
    rnd.recover_keys("key/l2_key_det", "key/l2_key_ope");
    string cipher_rnd = rnd.Encrypt(cipher_det, cipher_ope);
    cout << "cipher_rnd: " << cipher_rnd << endl << endl;

    cout << "decrypt cipher_rnd to cipher_det: " << rnd.Decrypt(cipher_rnd, rnd.keys[0]) << endl;
    cout << "decrypt cipher_rnd to cipher_ope: " << rnd.Decrypt(cipher_rnd, rnd.keys[1]) << endl;
  }

  return 0;
}
