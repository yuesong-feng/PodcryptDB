#include "DET.h"
#include "util.h"
#include <iostream>
using namespace std;
int main(){
    DET det;
    det.recover_key_iv("key/l1_key_det", "key/det_iv");
    det.print_key();
    det.print_iv();

    string cipher = recover_str_hex("data/ciphertext_det");
    print_ciphertext(cipher);

    // string plain = det.Decrypt(cipher);
    int plain = det.Decrypt_int(cipher);
    cout << "The plaintext is: " << plain << endl;
    return 0;
}