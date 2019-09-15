#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef struct{
    vector<int> near;
}Audio;

vector<Audio> w_data;
vector<int> result, temp_stack;

int total_num = 0, min_dist = 9999;
int acc_dist = 0, push_count = 0, ban_num = 0;

bool check_in_list(int i, vector<int> res){
    if(find(res.begin(), res.end(), i) != res.end()) return true;
    else return false;
}
int get_all_distance(){
    int dist_sum = 0;
    for(int i = 0; i < temp_stack.size()-1; i++){
        for(int j = i+1; j < temp_stack.size(); j++){
            if(check_in_list(temp_stack[j], w_data[temp_stack[i]-1].near)) dist_sum += j-i;
        }
    }
    return dist_sum;
};
void graph_search(Audio target, int prev){
    if(temp_stack.size() == total_num){
        // 끝까지 도달하는 경우의 수를 구함
        acc_dist = get_all_distance();
        if(acc_dist < min_dist){
            min_dist = acc_dist;
            result = temp_stack;
        }
        ban_num = 0;
        temp_stack.pop_back();
    }
    else{
        push_count = 0;
        /*
         42
         4 1 9 5 6 10 2 7 3 8
         */
        for(int i = 0; i < target.near.size(); i++){
            if(!check_in_list(target.near[i], temp_stack) && (target.near[i] != ban_num)){
                ban_num = 0;
                temp_stack.push_back(target.near[i]);
                push_count++;
                graph_search(w_data[target.near[i]-1], target.near[i]);
            }
            else if(target.near.front() != temp_stack.back()){
                target = w_data[temp_stack.back()-1];
                i = 0;
            }
        }
        if(push_count == 0){
            ban_num = prev;
            temp_stack.pop_back();
        }
        else{
            push_count = 0;
            ban_num = 0;
        }
    }
}
void input_data(){
    ifstream inFile("3.inp");
    Audio temp;
    int sign = 0;
    
    inFile >> total_num;
    for(int i = 0; i < total_num; i++){
        do{
            inFile >> sign;
            temp.near.push_back(sign);
        }while(sign != 0);
        temp.near.pop_back();
        w_data.push_back(temp);
        temp.near.clear();
    }
    inFile.close();
}
void output_data(){
    ofstream outFile("audio.out");
    vector<int>::iterator iter;
    
    outFile << min_dist << endl;
    cout << min_dist << endl;

    for(iter = result.begin(); iter != result.end(); iter++){
        outFile << (*iter) << " ";
        cout << (*iter) << " ";
    }
    outFile << endl;
    cout << endl;
    outFile.close();
}
int main(int argc, const char * argv[]) {
    input_data();
    for(int i = 0; i < total_num; i++){
        temp_stack.clear();
        temp_stack.push_back(i+1);
        graph_search(w_data[i], w_data[i].near.front());
    }
    output_data();
    return 0;
}
