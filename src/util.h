#pragma once
#include <string>
#include <cstring>
using namespace std;

void print_ciphertext(const string &ciphertext);

void store_str_hex(const string &ciphertext, const char* path);
string recover_str_hex(const char* path);

void store_str(const string &ciphertext, const char* path);
string recover_str(const char* path);

string tohex(const string &str);
string fromhex(const string& str);

struct EncodedTuple
{
    size_t len;
    uint8_t tuple[4]; // for simplicity
    EncodedTuple(string str)
    {
        *reinterpret_cast<uint32_t *>(tuple) = stoul(str);
        len = sizeof(uint32_t);
    }
    ~EncodedTuple() {}
};
#define MIN(x, y) ((x <= y) ? x : y)
// return -1, 0, 1 for t1 < t2, t1==t2, and t1 > t2, respectively
int compTuple(const EncodedTuple &t1, const EncodedTuple &t2);