/*
//
//  diet.cpp
//  A10-diet
//
//  Created by Young-il Seo on 14/05/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct{
    int mp;
    int mf;
    int ms;
    int mv;
    int price;
}Node;

int total_num;
int total_sum = 0;
Node target;
Node min_sum;
vector<Node> w_data;
vector<vector<int>> r_dvec;
vector<int> r_vec;
int min_price = 0;

void dfs(int i, Node n, vector<int> r){
    n.mp = n.mp + w_data[i].mp;
    n.mf = n.mf + w_data[i].mf;
    n.ms = n.ms + w_data[i].ms;
    n.mv = n.mv + w_data[i].mv;
    
    if(n.mf >= target.mf && n.mp >= target.mp && n.ms >= target.ms && n.mv >= target.mv){
        if(i >= w_data.size() - 1) return;
        if(total_sum < n.price){
            n.mp = n.mp - w_data[i].mp;
            n.mf = n.mf - w_data[i].mf;
            n.ms = n.ms - w_data[i].ms;
            n.mv = n.mv - w_data[i].mv;
            dfs(i+1, n, r);
        }
        else{
            r[i]++;
            dfs(i+1, n, r);
            
            n.mp = n.mp - w_data[i].mp;
            n.mf = n.mf - w_data[i].mf;
            n.ms = n.ms - w_data[i].ms;
            n.mv = n.mv - w_data[i].mv;
            r[i]--;
            dfs(i+1, n, r);
        }
    }
    else{
        if(n.price < total_sum){
            total_sum = n.price;
            r[i]++;
            
            if(!r_vec.empty()){
                if(r_vec.back() > total_sum){
                    r_dvec.clear();
                    r_vec.clear();
                }
            }
            
            r_dvec.push_back(r);
            r_vec.push_back(total_sum);
            r[i]--;
        }
        if(n.price == total_sum){
            r[i]++;
            r_dvec.push_back(r);
            r_vec.push_back(total_sum);
            r[i]--;
        }
        if(i >= w_data.size() - 1) return;
        n.mp = n.mp - w_data[i].mp;
        n.mf = n.mf - w_data[i].mf;
        n.ms = n.ms - w_data[i].ms;
        n.mv = n.mv - w_data[i].mv;
        dfs(i+1, n, r);
    }
}

void input_data(){
    Node temp;
    ifstream inFile("1.inp");
    inFile >> total_num;
    inFile >> target.mp >> target.mf >> target.ms >> target.mv;
    
    for(int i = 0; i < total_num; i++){
        inFile >> temp.mp >> temp.mf >> temp.ms >> temp.mv >> temp.price;
        total_sum += temp.price;
        w_data.push_back(temp);
    }
    inFile.close();
}
void output_data(){
    ofstream outFile("diet.out");
    vector<int>::iterator iter;
    for(iter = r_vec.begin(); iter != r_vec.end(); iter++){
        outFile << (*iter) << " ";
        cout << (*iter) << " ";
    }
    cout << endl;
    outFile.close();
}

int main(int argc, const char * argv[]) {
    input_data();
    Node temp;
    vector<int> result(total_num, 0);
    temp.mf = 0;
    temp.mp = 0;
    temp.ms = 0;
    temp.mv = 0;
    temp.price = 0;
    dfs(0, temp, result);
    output_data();
    
    return 0;
}
*/
