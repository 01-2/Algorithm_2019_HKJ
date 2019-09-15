//
//  read.cpp
//  A12-read
//
//  Created by Young-il Seo on 28/05/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

vector<string> w_data(500000);
int data_count = 0;

void input_data(){
    ifstream inFile("read.inp");
    string temp;
    
    if(!inFile.is_open()){
        cout << "[FILE] INPUT FAILED" << endl;
        return;
    }
    else{
        while(!inFile.eof()){
            inFile >> temp;
            w_data[data_count] = temp;
            data_count++;
        }
    }
    inFile.close();

}
string count_dna(vector<string>::iterator start, vector<string>::iterator end){
    int cnt = 0, r_cnt = 0;
    string temp, result;

    for(start = w_data.begin(); start != end; start++){
        if(temp != (*start)){
            if(cnt > r_cnt){
                result = temp;
                r_cnt = cnt;
            }
            temp = (*start);
            cnt = 0;
        }
        else cnt++;
    }
    return result;
}
void output_data(string res){
    ofstream outFile("read.out");
    outFile << res;
    outFile.close();
}
int main(int argc, const char * argv[]) {
    string result;
    vector<string>::iterator iter, iter_e;
    
    input_data();
    iter_e = next(w_data.begin(), data_count);
    sort(w_data.begin(), iter_e);
    result = count_dna(iter, iter_e);
    cout << result << endl;
    output_data(result);
    return 0;
}
