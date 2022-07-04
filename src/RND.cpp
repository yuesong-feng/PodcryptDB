#include "RND.h"
#include <string.h>
#include <unordered_set>
#include <random>
#include <iostream>
#include <ctime>
#include "util.h"

RND::RND() {}
RND::~RND() {}

string RND::Encrypt(const string &str1, const string &str2){
    string key1 = keys[0];
    string key2 = keys[1];

    // string key1 = "5-7-7-8-0-2";
    // string key2 = "2-3-8-10-3-5";

    char cipher[str1.size() + str2.size()];

    int start1 = 0;
    for(pair<int, int> &p : key_to_pairs(key1)){
        memcpy(cipher + p.first, str1.c_str() + start1, p.second - p.first);
        start1 = start1 + p.second - p.first;
    }

    int start2 = 0;
    for(pair<int, int> &p : key_to_pairs(key2)){
        memcpy(cipher + p.first, str2.c_str() + start2, p.second - p.first);
        start2 = start2 + p.second - p.first;
    }
    string res(cipher, str1.size() + str2.size());
    return res;
}

string RND::Decrypt(const string &cipher, const string &key){
    string ret;
    vector<pair<int, int>> pairs = key_to_pairs(key);
    for(pair<int, int> &each : pairs){
        string tmp(cipher, each.first, each.second - each.first);
        ret.append(tmp);
    }
    return ret;
}

// helper function, generate num random numbers between [min, max], no repeation
vector<int> RNDvector(int num, int min, int max){
    vector<int> ret(num);
    unordered_set<int> set;
    for(int i=0; i<num; i++){
        while(true){
            int rnd = min + rand() % (max+1 - min);
            if( set.count(rnd) == 0){
                set.insert(rnd);
                ret[i] = rnd;
                break;
            }
        }
    }
    return ret;
}

vector<string> RND::generate_key(int size1, int size2, int cut1, int cut2){
    string key1, key2;
    vector<int> blocks; // block size of each cut
    srand(time(nullptr));

    // generate blocks' length for str1 and str2: blocks
    int len = size1;
    for(int i=1; i<cut1; i++){
        int block = 1 + rand() % (len - cut1+i);
        blocks.push_back(block);
        len -= block;
    }
    blocks.push_back(len);
    len = size2;
    for(int i=1; i<cut2; i++){
        int block = 1 + rand() % (len - cut2+i);
        blocks.push_back(block);
        len -= block;
    }
    blocks.push_back(len);
    
    // generate the random order for all blocks and compute the offset
    vector<int> order = RNDvector(cut1+cut2, 0, cut1+cut2-1);
    vector<int> offsets(cut1+cut2);
    for(int i=0; i<cut1+cut2; i++){
        offsets[order[i]] = blocks[i];
    }
    for(int i=0, sum=0; i<cut1+cut2; i++){
        int cur = offsets[i];
        offsets[i] = sum;
        sum += cur;
    }

    for(int i=0; i<cut1+cut2; i++){
        int s = offsets[order[i]];
        int e = s + blocks[i];
        if( i < cut1){
            key1 += to_string(s) + "-" + to_string(e) + "-";
        }
        else{
            key2 += to_string(s) + "-" + to_string(e) + "-";
        }
    }

    key1 = string(key1.begin(), key1.end()-1);
    key2 = string(key2.begin(), key2.end()-1);
    // std::cout<<key1<<std::endl<<key2<<std::endl;
    keys.clear();
    keys.push_back(key1);
    keys.push_back(key2);
    return vector<string> {key1, key2};
}



vector<pair<int, int>> RND::key_to_pairs(const string &key){
    string k = key + "-";
    vector<pair<int, int>> pairs;
    string tmp;
    pair<int, int> p;
    int loc = 1;
    for(int i = 0; i < k.size(); ++i){
        if(k[i] != '-'){
            tmp.push_back(k[i]);
            continue;
        }
        if(loc == 1){
            p.first = stoi(tmp);
            loc = 2;
        } else if(loc == 2){
            p.second = stoi(tmp);
            pairs.push_back(p);
            loc = 1;
        }
        tmp.clear();
    }
    return pairs;
}

void RND::recover_keys(const char* l2_det_path, const char* l2_ope_path){
    string l2_key_det = recover_str_hex(l2_det_path);
    string l2_key_ope = recover_str_hex(l2_ope_path);
    keys = {l2_key_det, l2_key_ope};
}

void RND::store_keys(const char* l2_det_path, const char* l2_ope_path){
    store_str_hex(keys[0], l2_det_path);
    store_str_hex(keys[1], l2_ope_path);
}