#include "DET.h"
#include "util.h"
#include <iostream>
using namespace std;
int main(){
    DET det;
    det.GenerateKey();
    det.print_key();
    det.print_iv();
    det.store_key_iv("key/l1_key_det", "key/det_iv");

    // string plaintext = "Hello world!";
    int plaintext = 123;
    cout << "The plaintext is: " << plaintext << endl;

    string cipher = det.Encrypt_int(plaintext);
    print_ciphertext(cipher);

    store_str_hex(cipher, "data/ciphertext_det");
    return 0;
}