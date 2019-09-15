//
//  copy.cpp
//  A6-copy
//
//  Created by Young-il Seo on 04/04/2019.
//  Copyright © 2019 Young-il Seo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <string>
#include <regex>

using namespace std;

int get_LCS(wstring base, wstring target){
    int LCS[100][100];
    memset(LCS, 0, sizeof(LCS));
    
    for(int i = 1; i <= target.length(); i++){
        for(int j = 1; j <= base.length(); j++){
            if(target[i-1] == base[j-1])
                LCS[i][j] = LCS[i-1][j-1] + 1;
            else
                LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
        }
    }
    for(int i = 0; i <= target.length(); i++){
        for(int j = 0; j <= base.length(); j++){
            cout << LCS[i][j] << " ";
        }
        cout << endl;
    }
    
    return LCS[target.length()][base.length()];
}

double get_sim(wstring base, wstring target){
    int lcs_val = get_LCS(base, target);
    double sim_val = (double)(2 * lcs_val) / (double)(base.size() + target.size());
    return sim_val;
}

void rep_space(wstring &t){
    wregex space(L"[\\s]+");
    t = regex_replace(t, space, L" ");
}

void rep_duplicate(wstring &t){
    wregex eulrul(L"[을|를]");
    wregex eunnun(L"[은|는]");
    t = regex_replace(t, eulrul, L"을");
    t = regex_replace(t, eunnun, L"은");
}

void process_string(vector<wstring>& s_vec){
    vector<wstring>::iterator iter;
    for(iter = s_vec.begin(); iter != s_vec.end(); iter++){
        rep_space(*iter);
        rep_duplicate(*iter);
    }
}

int main() {
    int size = 0;
    int result = 0;
    double temp = 0;
    double max_sim = 0;
    
    vector<wstring> s_vec;
    vector<wstring>::iterator iter;
    
    ios::sync_with_stdio(false);
    
    locale loc("en_US.UTF-8");
    wcout.imbue(loc); // Use it for output
    
    // input
    wfstream file("4.inp");
    file.imbue(loc); // Use it for file input
    
    wstring str;
    getline(file, str); // str.size() will be 6
    size = stoi(str);
    
    for(int i = 0; i < size; i++){
        getline(file, str);
        s_vec.push_back(str);
    }
    
    process_string(s_vec);
    
    for(int i = 1; i < size; i++){
        temp = get_sim(s_vec[0], s_vec[i]);
        if(temp > max_sim){
            max_sim = temp;
            result = i;
        }
    }
    
    result++;
    
    cout << result << endl;
    // output
    
    wofstream out("copy.out");
    out.imbue(loc); // Use it for file input
    out << result;
    out.flush();
}
