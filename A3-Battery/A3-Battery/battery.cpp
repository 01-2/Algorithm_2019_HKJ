//
//  battery.cpp
//  A3-Battery
//
//  Created by Young-il Seo on 21/03/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

typedef struct{
    int left;
    int mid;
    int right;
}Range;

class Pos{
public:
    int x, y;
    bool checked;
    
    Pos(){
        x =0; y=0; checked = false;
    }
    Pos(int xx, int yy){
        x = xx; y= yy; checked = false;
    }
};

int input_data(vector<Pos>& p_list){
    ifstream inFile("battery.inp");
    int num_line = 0, end_pos = 0;
    Pos inp_pos;

    if(inFile.fail()) return 1;
    
    inFile >> num_line >> end_pos;
    
    for(int i = 0; i < num_line; i++){
        inFile >> inp_pos.x >> inp_pos.y;
        inp_pos.checked = false;
        p_list.push_back(inp_pos);
    }
    
    inp_pos.x = end_pos;
    inp_pos.y = end_pos;
    p_list.push_back(inp_pos);
    
    return 0;
}

int output_data(int w){
    ofstream outFile("battery.out");
    
    if(outFile.fail()) return 1;
    
    outFile << w;
    outFile.close();
    
    return 0;
}

int get_dist(Pos a, Pos b){
    return ceil(sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2)));
}

bool trace_route(vector<Pos> p_list, int w){
    vector<Pos> route;
    vector<Pos>::iterator p_iter;
    vector<Pos>::iterator r_iter;
    queue<Pos> q;
    
    Pos end = p_list.back();
    
    Pos temp;
    temp.x = 0;
    temp.y = 0;
    temp.checked = true;
    route.push_back(temp);
    q.push(temp);
    
    p_list.pop_back();
    
    while(!q.empty()){
        int x = q.front().x;
        int y= q.front().y;
        q.pop();
        
        if(get_dist(Pos(x, y), end) <= w)
            return true;
        
        for(int i = 0; i < p_list.size(); i++){
            int nx = p_list[i].x, ny = p_list[i].y;
            
            if(p_list[i].checked)
                continue;
            
            if(get_dist(Pos(x, y), Pos(nx, ny)) <= w){
                p_list[i].checked = true;
                q.push(p_list[i]);
            }
        }
    }
    return false;
}

int optimized_dist(vector<Pos> p_list){
    int opt_w = 0;
    Range r;
    
    r.left = 0;
    r.right = get_dist(p_list[0], p_list[p_list.size()-1]);
    
    while(r.left <= r.right){
        r.mid = (r.left + r.right) / 2;
        if(trace_route(p_list, r.mid)){
            r.right = r.mid - 1;
            opt_w = r.mid;
        }
        else r.left = r.mid + 1;
    }
    return opt_w;
}

int main(int argc, const char * argv[]) {
    vector<Pos> pos_list;
    int opt_w = 0;
    
    if(input_data(pos_list)){
        cout << "[ERROR] READ FAILED" << endl;
        return 1;
    };
    
    opt_w = optimized_dist(pos_list);
    cout << "Optimized distance : " << opt_w << endl;
    
    if(output_data(opt_w)){
        cout << "[ERROR] WRITE FAILED" << endl;
        return 1;
    }
    
    return 0;
}
