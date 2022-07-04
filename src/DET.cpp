#include "DET.h"
#include <iostream>
#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/des.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "util.h"

#define KEY_LEN DES::DEFAULT_KEYLENGTH
#define IV_LEN DES::BLOCKSIZE

DET::DET() : key(nullptr), iv(nullptr){ 
	key = new SecByteBlock(KEY_LEN);
	iv = new byte[IV_LEN];
}

DET::~DET () {
	delete key;
	delete iv;
}

void DET::GenerateKey(){
    AutoSeededRandomPool prng;
	prng.GenerateBlock(*key, key->size());
	prng.GenerateBlock(iv, IV_LEN);
}

string DET::Encrypt(const string &plaintext){
	string ciphertext;
	try{
    	CBC_Mode< DES >::Encryption encryptor;
		encryptor.SetKeyWithIV(*key, key->size(), iv);

    	// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(plaintext, true, 
			new StreamTransformationFilter(encryptor,
				new StringSink(ciphertext)
			) // StreamTransformationFilter
		); // StringSource
	} catch(const CryptoPP::Exception& e){
		cerr << e.what() << endl;
		exit(1);
	}
    return ciphertext;
}

string DET::Decrypt(const string &ciphertext){
    string recover;
    try {
        CBC_Mode< DES >::Decryption decryptor;
		decryptor.SetKeyWithIV(*key, key->size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(ciphertext, true, 
			new StreamTransformationFilter(decryptor,
				new StringSink(recover)
			) // StreamTransformationFilter
		); // StringSource
    } catch(const CryptoPP::Exception& e) {
        cerr << e.what() << endl;
		exit(1);
    }
    return recover;
}

string DET::Encrypt_int(const int plaintext){
	string pt_str = to_string(plaintext);
	return tohex(this->Encrypt(pt_str));
}
int DET::Decrypt_int(const string &ciphertext){
	string str = this->Decrypt(fromhex(ciphertext));
	return stoi(str);
}

void DET::print_key(){
    // Pretty print key
	string encoded;
	StringSource(*key, key->size(), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;
}
void DET::print_iv(){
	// Pretty print iv
	string encoded;
	StringSource(iv, DES::BLOCKSIZE, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "iv: " << encoded << endl;
}

void DET::store_key_iv(const string &key_path, const string &iv_path){
	ArraySource(*key, key->size(), true,
		new HexEncoder(
			new FileSink(key_path.c_str())
		) // HexEncoder
	); // StringSource
	StringSource(iv, DES::BLOCKSIZE, true,
		new HexEncoder(
			new FileSink(iv_path.c_str())
		) // HexEncoder
	); // StringSource
	// cout << "key stored to " << key_path << endl;
	// cout << "iv stored to " << iv_path << endl;
}

void DET::recover_key_iv(const string &key_path, const string &iv_path){
	FileSource(key_path.c_str(), true, 
		new HexDecoder(
			new ArraySink(*key, KEY_LEN)
		)
	);
	FileSource(iv_path.c_str(), true, 
		new HexDecoder(
			new ArraySink(iv, IV_LEN)
		)
	);
}

