//
//  ct.cpp
//  A9-CT
//
//  Created by Young-il Seo on 01/05/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int n = 0;
vector<int> ray_1, ray_2, ray_3, ray_4;
vector<vector<char>> table;
int xx[] = { -1, 0, 1, 0 };
int yy[] = { 0, 1, 0, -1 };
ofstream outFile("ct.out");


void input_file(){
    int temp = 0;
    ifstream inFile("ct.inp");
    
    inFile >> n;
    
    for(int i = 0; i < n; i++){
        inFile >> temp;
        ray_1.push_back(temp);
    }
    
    for(int i = 0; i < n; i++){
        inFile >> temp;
        ray_2.push_back(temp);
    }
    
    for(int i = 0; i < (2 * n -1); i++){
        inFile >> temp;
        ray_3.push_back(temp);
    }
    
    for(int i = 0; i < (2 * n -1); i++){
        inFile >> temp;
        ray_4.push_back(temp);
    }
    
    inFile.close();
}

bool isRange( int r, int c ) {
    if ( r >= 0 && r < n+2 && c >= 0 && c < n+2 )
        return true;
    return false;
}

int getBlock(int r, int c, char k) {
    int count = 0;
    vector<vector<bool>> visit(n+2, vector<bool>(n+2, false));
    visit[r][c] = true;
    queue<pair<int, int>> que;
    que.push({r, c});
    while ( !que.empty() ) {
        pair<int, int> temp = que.front();
        que.pop();
        count++;
        for ( int i = 0; i < 4; i++ ) {
            int R = temp.first + xx[i];
            int C = temp.second +yy[i];
            if ( isRange(R,C) && table[R][C] == k && visit[R][C] == false ) {
                visit[R][C] = true;
                que.push({R,C});
            }
        }
    }
    return count;
}

bool setBlock(int idx, int count, int column) {
    if ( column ==  n+1 ) {
        pair<int, int> block = { 0, 0 };
        for ( int r = 0; r < n+2; r++ )
            for ( int c = 0; c < n+2; c++ )
                if (table[r][c] == 'B')
                    block = {r, c};
        if ( getBlock(0, 0, '-') + getBlock(block.first, block.second, 'B') == pow(n+2, 2) ) {
            for ( int r = 1; r <= n; r++ )
                for ( int c = 1; c <= n; c++ )
                    outFile << table[r][c] << ((c == n) ? "\n" : " ");
            return true;
        } else
            return false;
    } else if ( count == ray_1[column-1] ) {
        if ( setBlock(0, 0, column+1) )
            return true;
    } else {
        for ( int i = idx+1; i <= n; i++ ) {
            if ( ray_2[i-1] >= 1 && ray_3[(i-1)+(n-column)] >= 1 && ray_4[(i-1)+(column-1)] >= 1 ) {
                table[i][column] = 'B';
                ray_2[i-1]--;
                ray_3[(i-1)+(n-column)]--;
                ray_4[(i-1)+(column-1)]--;
                if ( setBlock(i, count+1, column) )
                    return true;
                ray_3[(i-1)+(n-column)]++;
                ray_4[(i-1)+(column-1)]++;
                ray_2[i-1]++;
                table[i][column] = '-';
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    
    input_file();
    table.assign(n+2, vector<char>(n+2, '-'));
    setBlock(0, 0, 1);
    outFile.close();

    return 0;
}
