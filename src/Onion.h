#pragma once
#include "DET.h"
#include "OPE.h"
#include "RND.h"
#include <string>
using namespace std;

class Onion{
public:
    DET *p_det;
    OPE *p_ope;
    RND *p_rnd;
public:
    Onion();
    ~Onion();
    string Encrypt(int num);
    string Decrypt(const string& cipher_rnd, const string& l2_key);
};