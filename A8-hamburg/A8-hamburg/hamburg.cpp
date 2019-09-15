//
//  hamburg.cpp
//  A8-hamburg
//
//  Created by Young-il Seo on 30/04/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

int k, n;
int result = 0;
vector<char> alloc;

vector<int> input_data(){
    char stemp;
    vector<int> p_pos;
    ifstream inFile("hamburg.inp");
    inFile >> k >> n;

    for(int i = 0; i < n; i++){
        inFile >> stemp;
        if(strncmp(&stemp, "P", 1) == 0) p_pos.push_back(i);
        alloc.push_back(stemp);
        cout << stemp << " ";
    }
    cout << endl;
    inFile.close();
    return p_pos;
}
void output_data(int result){
    ofstream outFile("hamburg.out");
    outFile << result;
    cout << result;
    outFile.close();
}
vector<pair<int, int>> find_hamburg_max(vector<int> p_pos){
    pair<int, int> pos;
    vector<pair<int, int>> pair_list;
    vector<int>::iterator p_iter;
    
    for(p_iter = p_pos.begin(); p_iter != p_pos.end(); p_iter++){
        int left = (*p_iter) - k;
        int right = (*p_iter) + k;
        
        if(left < 0) left = 0;
        if(right > alloc.size() - 1) right = (int)(alloc.size() - 1);
        
        pos = make_pair(left, right);
        cout << "(" << pos.first << " , " << pos.second << ")" << endl;
        pair_list.push_back(pos);
    }
    
    return pair_list;
}
int find_result(vector<pair<int, int>> target){
    int result = 0;
    vector<pair<int, int>>::iterator iter;
    for(iter = target.begin(); iter != target.end(); iter++){
        for(int i = (*iter).first; i < ((*iter).second + 1); i++){
            if(strncmp(&alloc[i], "H", 1) == 0){
                alloc[i] = 'X';
                result++;
                break;
            }
        }
    }
    return result;
}
int main(int argc, const char * argv[]) {
    int result = 0;
    vector<int> p_pos;
    vector<pair<int, int>> pair_list;
    
    p_pos = input_data();
    pair_list = find_hamburg_max(p_pos);
    result = find_result(pair_list);
    output_data(result);
    
    return 0;
}
