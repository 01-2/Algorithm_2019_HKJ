//
//  oil.cpp
//  A4-oil
//
//  Created by Young-il Seo on 26/03/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "oil.h"

using namespace std;

typedef struct{
    int a;
    int b;
}Pos;

vector<Pos> divide_range(int a, int b){
    Pos beg, end;
    vector<Pos> d_range;
    int half_point = (b + a) / 2;
    
    beg.a = a;
    beg.b = half_point;
    end.a = half_point+1;
    end.b = b;
    
    d_range.push_back(beg);
    d_range.push_back(end);
    
    return d_range;
}

int find_str_pt(Pos range){
    int checker = -1;
    int position = 0;
    
    vector<Pos> d_range;
    d_range = divide_range(range.a, range.b);
    checker = observe(d_range[0].a, d_range[0].b);
    
    if(checker == 1) position = d_range[0].a;
    else if(checker == 2) position = find_str_pt(d_range[0]);
    else position = find_str_pt(d_range[1]);
    return position;
}

int find_fin_pt(Pos range){
    int checker = -1;
    int position = 0;
    
    vector<Pos> d_range;
    d_range = divide_range(range.a, range.b);
    checker = observe(d_range[1].a, d_range[1].b);
    
    if(checker == 1) position = d_range[1].b;
    else if(checker == 2) position = find_fin_pt(d_range[1]);
    else position = find_fin_pt(d_range[0]);
    return position;
}

Pos find_optimal_range(){
    Pos inp;
    Pos opt_ans;
    
    inp.a = 0;
    inp.b = oil_size()-1;
    
    opt_ans.a = find_str_pt(inp);
    opt_ans.b = find_fin_pt(inp);

    return opt_ans;
}

int main(int argc, const char * argv[]) {
    Pos answer;
    initial();
    
    answer = find_optimal_range();
    oil_report(answer.a, answer.b);
    
    return 0;
}
