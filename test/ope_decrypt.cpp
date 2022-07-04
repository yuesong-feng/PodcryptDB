#include "OPE.h"
#include "util.h"
#include <iostream>
using namespace std;
int main(){
    OPE ope;
    string cipher = recover_str_hex("data/ciphertext_ope");

    print_ciphertext(cipher);
    
    int plain = ope.Decrypt_int(cipher);
    cout << "The plaintext is: " << plain << endl;
    
    return 0;
}