//
//  bridge.cpp
//  A2-Bridge
//
//  Created by Young-il Seo on 13/03/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

double min_dist;

typedef struct{
    double x;
    double y;
    double z;
}Pos;

typedef struct{
    double left;
    double mid;
    double right;
}Range;

double get_distance(Pos a, Pos b){
    double dist = 0;
    dist = sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2) + pow((b.z - a.z),2));
    return dist;
}

Pos get_center(Pos a, Pos b){
    // S(t) = t * B + (1 - t) * A
    Pos center;
    
    center.x = 0.5 * (a.x + b.x);
    center.y = 0.5 * (a.y + b.y);
    center.z = 0.5 * (a.z + b.z);
    
    return center;
}

void get_min_distance(Range r, Pos a, Pos b, Pos p){
    
    /*
     if((ceil(r.left) == ceil(r.mid)) && (ceil(r.right) == ceil(r.mid))
       || (r.left == r.right)){
        min_dist = ceil(r.mid);
        return;
    }*/
    if(((r.left == r.right) && (r.mid == r.right)) || (r.left == r.right)){
        min_dist = ceil(r.mid);
        return;
    }
    else{
        Pos center;
        
        r.left = get_distance(a, p);
        r.right = get_distance(b, p);
        
        center = get_center(a, b);
        r.mid = get_distance(center, p);
        
        if((r.left > r.mid) && (r.left > r.right)){
            r.left = r.mid;
            a = center;
            get_min_distance(r, a, b, p);
        }
        else if((r.right > r.mid) && (r.right > r.left)){
            r.right = r.mid;
            b = center;
            get_min_distance(r, a, b, p);
        }
    }
}

int main(int argc, const char * argv[]) {
    Pos temp;
    Range target;
    
    vector<Pos> pos_list;
    ifstream inFile("bridge.inp");
    ofstream outFile("bridge.out");
    
    // Input process
    if(inFile.fail()){
        cout << "File read error" << endl;
        return 1;
    }
    
    // Input sequence : A, B, P
    for(int i = 0; i < 3; i++){
        inFile >> temp.x >> temp.y >> temp.z;
        pos_list.push_back(temp);
    }
    inFile.close();
    
    /*
     Logic :
        S(t) = t * B + (1 - t) * A
        모든 좌표에 적용. 구해지는 값이랑 점과 점 사이의 거리 공식을 이용하여 최단거리 산출
        좌측, 우측, 중점을 구하고, 가장 긴 쪽을 버리고 그 쪽을 중점으로 변환
     */
    temp = get_center(pos_list[0], pos_list[1]);
    
    target.left = get_distance(pos_list[0], pos_list[2]);
    target.right = get_distance(pos_list[1], pos_list[2]);
    target.mid = get_distance(pos_list[2], temp);
    
    get_min_distance(target, pos_list[0], pos_list[1], pos_list[2]);
    cout << static_cast<int>(min_dist) << endl;
    outFile << static_cast<int>(min_dist) << endl;
    outFile.close();
    return 0;
}
