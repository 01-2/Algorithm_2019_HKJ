//
//  main.cpp
//  A1-Palindrome
//
//  Created by Young-il Seo on 04/03/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {

    ifstream inFile("palin.inp");
    ofstream outFile("palin.out");
    /* Logic :
        - 양쪽 끝에서 확인했을 때 문자가 일치했을 경우 전체 길이에서 2씩 제외해줌
        - 문자가 일치하지 않았을 경우, 유사회문, 유사회문이 아니라면 일반 문자열로 구분
        - 유사회문 = 안되는 지점에서 한쪽을 빼고 진행했을 경우 가능한가를 판단.
     */
    string target;
    string temp;
    
    int num_line = 0;
    int type = 0;
    
    if(inFile.fail()){
        cout << "File read error" << endl;
        return 1;
    }
    getline(inFile, target);
    num_line = stoi(target);

    for(int i = 0; i < num_line; i++){
        getline(inFile, target);
        target.pop_back();
        type = 0;
        while(target.front() == target.back()){
            target.erase(0,1);
            target.erase(target.length()-1,1);
            if(target.length() < 2){
                // Palindrome
                type = 1;
                break;
            }
        }
        /*
            상단 반복문에서 뒷 자리가 같은 경우 제거했기 때문에 이번에는 앞만 제거하고 진행해보거나
            뒤만 빼고 진행해보면 됨. 만약 그 중 하나가 성공했다면 유사회문
         */
        if(type != 1){
            temp = target;
            target.erase(0,1);
            while(target.front() == target.back()){
                target.erase(0,1);
                target.erase(target.length()-1,1);
                if(target.length() < 2){
                    type = 2;
                    break;
                }
            }
            
            temp.erase(temp.length()-1, 1);
            while(temp.front() == temp.back()){
                temp.erase(0,1);
                temp.erase(temp.length()-1,1);
                if(temp.length() < 2){
                    type = 2;
                    break;
                }
            }
            if(type != 2){
                type = 3;
            }
        }
        outFile << type << endl;
        cout << type << endl;
    }
    
    inFile.close();
    outFile.close();
    return 0;
}
