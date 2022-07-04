#include "OPE.h"
#include "util.h"
#include <iostream>
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
using namespace std;
using namespace CryptoPP;

int main()
{
    OPE ope;
    int plain = 123;
    cout << "The plaintext is: " << plain << endl;

    string cipher = ope.Encrypt_int(plain);
    print_ciphertext(cipher);
    store_str_hex(cipher, "data/ciphertext_ope");

    return 0;
}