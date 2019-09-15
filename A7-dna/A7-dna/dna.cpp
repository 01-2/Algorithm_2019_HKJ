//
//  dna.cpp
//  A7-dna
//
//  Created by Young-il Seo on 09/04/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct{
    int x;
    int y;
}Pos;

string base;
string target;
string result;

int count;
int match_map[100][100];
vector<string> str_list;

int input_data(){
    ifstream inFile("test1.inp");
    if(inFile.fail()) return 1;
    
    inFile >> base;
    inFile >> target;
    
    inFile.close();
    return 0;
}
int output_data(){
    ofstream outFile("dna.out");
    if(outFile.fail()) return 1;
    
    outFile.close();
    return 0;
}
void get_map(string b, string t){
    memset(match_map, 0, sizeof(match_map));
    for(int i = 0; i < b.length(); i++){
        for(int j = 0; j < t.length(); j++){
            if(b[i] == t[j]) match_map[i][j] = 1;
        }
    }
}
void print_map(){
    for(int i = 0; i < base.length(); i++){
        for(int j = 0; j < target.length(); j++){
            cout << match_map[i][j] << " ";
        }
        cout << endl;
    }
}
void get_start_pos(vector<Pos> &s_pos){
    Pos temp;
    for(int i = 0; i< base.length(); i++){
        for(int j = 0; j < target.length(); j++){
            if(match_map[i][j] == 1){
                temp.x = i;
                temp.y = j;
                s_pos.push_back(temp);
            }
        }
    }
}
vector<Pos> match_box(Pos init){
    Pos temp;
    int box[2][2];
    vector<Pos> match_pos;
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            box[i][j] = match_map[init.x+i+1][init.y+j+1];
            if(box[i][j] == 1){
                temp.x = init.x+i+1;
                temp.y = init.y+j+1;
                match_pos.push_back(temp);
            }
        }
    }
    return match_pos;
}
void func1(Pos inp){
    vector<Pos> temp;
    vector<Pos>::iterator iter;
    
    temp = match_box(inp);
    if(temp.empty()){
        // result.push_back(base[inp.x]);
        return;
    }
    else{
        for(iter = temp.begin(); iter != temp.end(); iter++){
            func1(*iter);
            result.push_back(base[inp.x]);
        }
    }
}

/*
 Logic
 1. Match map을 구하고 1의 position을 모두 구한 다음 DFS 실시
 2. 2x2 칸 안에 조건을 만족시키지 못한다면 탈락, 만족시킨다면 recursive 하게 순환 시켜서 문자열을 찾음
 3. 문자열을 찾은 후 후보군을 추려서 사전 순으로 나열, 내려갈수록 가중치 증가
 */

int main(int argc, const char * argv[]) {
    vector<Pos> start_pos;
    vector<Pos> match_pos;
    vector<Pos>::iterator iter;
    vector<string> candidate;
    
    if(input_data()){
        cout << "[ERROR] FILE INPUT FAILED" << endl;
        return 1;
    }
    
    get_map(base,target);
    get_start_pos(start_pos);
    for(iter = start_pos.begin(); iter != start_pos.end(); iter++){
        func1(*iter);
        reverse(result.begin(), result.end());
        candidate.push_back(result);
        cout << result << endl;
        result = "";
    }

//    if(output_data()){
//        cout << "[ERROR] FILE OUTPUT FAILED" << endl;
//        return 1;
//    }
    
    return 0;
}
