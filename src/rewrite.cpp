#include "rewrite.h"
#include "DET.h"
#include "util.h"
#include <iostream>
using namespace std;
string encrypt_sql(const string &sql){
    
    int start = -1, end = -1, value = 0;
    for(int i = 0; i < sql.size(); ++i){
        if(!isdigit(sql[i])){
            if(start != -1) end = i;
            start = -1;
            continue;
        }
        if(isdigit(sql[i]) && i >= 1 && isalpha(sql[i - 1])) continue;
        if(start == -1) start = i;
        value = value * 10 + sql[i];
    }
    cout << start << " " << end << " " << value << endl;

    DET det;
    det.recover_key_iv("key/l1_key_det", "key/det_iv");
    // sql: select * from numtest where age=18;
    string res = "select * from numtest where age='" + tohex( det.Encrypt_int(18) ) + "'";
    return res;
}

vector<vector<string>> decrypt_res(const vector<vector<string>> &res){
    DET det;
    vector<vector<string>> ret;
    for(auto &row : res){
        vector<string> each_row;
        for(auto &filed : row){
            each_row.push_back(to_string(det.Decrypt_int(filed)));
        }
        ret.push_back(each_row);
    }
    return ret;
}

