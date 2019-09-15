#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class record{
public:
    int p, f, s, v, c;
    record(){ p = 0; f = 0; s = 0; v = 0; c = 0; }
    record(int _p, int _f , int _s , int _v, int _c){
        p = _p; f = _f; s = _s; v = _v; c = _c;
    }
    record& operator +(record &b){
        p += b.p; f += b.f; s += b.s; v += b.v; c += b.c;
        return *this;
    }
    record& operator -(record &b){
        p -= b.p; f -= b.f; s -= b.s; v -= b.v; c -= b.c;
        return *this;
    }
};

int total_num = 0, total_sum = 0;

record target;
vector <record> w_data;

vector <vector <int>> result_dvec;
vector <int> result_vec;

void input_data(){
    ifstream inp("./diet.inp");
    
    inp >> total_num;
    inp >> target.p >> target.f >> target.s >> target.v;
    
    for(int i = 0; i < total_num; i++){
        int p, f, s, v, c;
        inp >> p >> f >> s >> v >> c;
        w_data.push_back(record(p, f, s , v, c));
        total_sum += c;
    }
    
    target.c = 0;
    inp.close();
}

void output_data(){
    ofstream out("./diet.out");
    for(int i = 0; i < total_num; i++){
        if(result_dvec.front()[i] != 0){
            out << i + 1 << " ";
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    out.close();
}

void dfs(vector <int> result, record rec, int index){
    rec = rec + w_data[index];

    if((rec.p >= target.p) && (rec.f >= target.f) && (rec.s >= target.s) && (rec.v >= target.v)){
        if(rec.c < total_sum){
            total_sum = rec.c;
            result[index]++;
 
            if(!result_vec.empty()){
                if(result_vec.back() > total_sum){
                    result_vec.clear();
                    result_dvec.clear();
                }
            }
            result_vec.push_back(total_sum);
            result_dvec.push_back(result);
            result[index]--;
        }
        if(rec.c == total_sum){
            result[index]++;
            result_vec.push_back(total_sum);
            result_dvec.push_back(result);
            result[index]--;
        }
        
        if(index == w_data.size() - 1) return;
        rec = rec - w_data[index];
        dfs(result, rec, index + 1);
    }
    else{
        if(index == w_data.size() -1) return;
        if(total_sum < rec.c){
            rec = rec - w_data[index];
            dfs(result, rec, index + 1);
        }
        else{
            result[index]++;
            dfs(result, rec, index + 1);
 
            rec = rec - w_data[index];
            result[index]--;
            dfs(result, rec, index + 1);
        }
    }
}

int main(){
    vector <int> result;
    record temp (0, 0, 0, 0, 0);
    
    input_data();
    for(int i = 0; i < total_num; i++) result.push_back(0);
    
    dfs(result, temp, 0);
    output_data();
 
    return 0;
}
