#include "util.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include <iostream>
using namespace CryptoPP;

void print_ciphertext(const string &ciphertext){
	// Pretty print
	string encoded;
	StringSource(ciphertext, true,
		new HexEncoder( 
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "cipher text: " << encoded << endl;
}

string tohex(const string &str){
	string res;
	StringSource(str, true,
		new HexEncoder( 
			new StringSink(res)
		) // HexEncoder
	); // StringSource}
	return res;
}
string fromhex(const string& str){
	string res;
	StringSource(str, true,
		new HexDecoder( 
			new StringSink(res)
		) // HexEncoder
	); // StringSource}
	return res;
}

void store_str_hex(const string &ciphertext, const char* path){
	StringSource(ciphertext, true,
		new HexEncoder( 
			new FileSink(path)
		) // HexEncoder
	); // StringSource
	// cout << "ciphertext stored to " << path << endl;
}

string recover_str_hex(const char* path){
	string cipher;
	FileSource(path, true, 
		new HexDecoder(
			new StringSink(cipher)
		)
	);
	return cipher;
}

void store_str(const string &ciphertext, const char* path){
	StringSource(ciphertext, true,
			new FileSink(path)
	); // StringSource
	// cout << "ciphertext stored to " << path << endl;
}

string recover_str(const char* path){
	string cipher;
	FileSource(path, true, 
			new StringSink(cipher)
	);
	return cipher;
}

// return -1, 0, 1 for t1 < t2, t1==t2, and t1 > t2, respectively
int compTuple(const EncodedTuple &t1, const EncodedTuple &t2)
{
    int rc = memcmp(t1.tuple, t2.tuple, MIN(t1.len, t2.len));
    if (rc == 0)
    {
        rc = (t1.len < t2.len) ? -1 : ((t1.len > t2.len) ? 1 : 0);
    }
    else
    {
        rc = (rc < 0) ? -1 : 1;
    }
    return rc;
}