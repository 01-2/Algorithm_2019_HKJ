//
//  palin.cpp
//  A1-Palindrome
//
//  Created by Young-il Seo on 04/03/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int check_palin(string str){
    while(str.front() == str.back()){
        str.pop_back();
        str.erase(0,1);
        if(str.length() < 2){
            return 1;
        }
    }
    return 0;
}

int check_pseudo(string str){
    string temp;
    
    while(str.front() == str.back()){
        str.pop_back();
        str.erase(0,1);
    }
    
    temp = str;
    str.pop_back();
    while(str.front() == str.back()){
        str.pop_back();
        str.erase(0,1);
        if(str.length() < 2){
            return 1;
        }
    }
    
    temp.erase(0,1);
    while(temp.front() == temp.back()){
        temp.pop_back();
        temp.erase(0,1);
        if(temp.length() < 2){
            return 1;
        }
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    /* Logic :
     - 양쪽 끝에서 확인했을 때 문자가 일치했을 경우 전체 길이에서 2씩 제외해줌
     - 문자가 일치하지 않았을 경우, 유사회문, 유사회문이 아니라면 일반 문자열로 구분
     - 유사회문 = 안되는 지점에서 한쪽을 빼고 진행했을 경우 가능한가를 판단.
     */
    
    ifstream inFile("palin.inp");
    ofstream outFile("palin.out");

    vector<string> target_list;
    vector<int> result_list;
    
    vector<string>::iterator viter;
    vector<int>::iterator iiter;
    
    string temp;
    int num_line = 0;
    
    if(inFile.fail()){
        cout << "File read error" << endl;
        return 1;
    }
    
    inFile >> num_line;
    
    // Input item
    for(int i = 0; i < num_line; i++){
        inFile >> temp;
        target_list.push_back(temp);
    }
    inFile.close();
    
    for(viter = target_list.begin(); viter != target_list.end(); viter++){
        if(check_palin(*viter)) result_list.push_back(1);
        else if(check_pseudo(*viter)) result_list.push_back(2);
        else result_list.push_back(3);
    }
    
    for(iiter = result_list.begin(); iiter != result_list.end(); iiter++){
        outFile << *iiter << endl;
        cout << *iiter << endl;
    }
    
    outFile.close();
    return 0;
}
