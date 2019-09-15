//#include <iostream>
//#include <fstream>
//#include <vector>
//
//#define ret return
//
//using namespace std;
//
//class nutrient{
//public:
//    int protein, fat, carb, vitamin;
//    int cost;
//    
//    nutrient(){
//        protein = 0; fat = 0; carb = 0; vitamin = 0;
//        cost = 0;
//    }
//    nutrient(int p, int f , int c , int v, int co){
//        protein = p; fat = f; carb = c; vitamin = v;
//        cost = co;
//    }
//    nutrient& operator +(nutrient &b){
//        protein += b.protein;
//        fat += b.fat;
//        carb += b.carb;
//        vitamin += b.vitamin;
//        cost += b.cost;
//        return *this;
//    }
//    nutrient& operator -(nutrient &b){
//        protein -= b.protein;
//        fat -= b.fat;
//        carb -= b.carb;
//        vitamin -= b.vitamin;
//        cost -= b.cost;
//        return *this;
//    }
//};
//
//nutrient minimum; int maxCost = 0;
//vector <nutrient> list;
//vector <vector <int>> answer;
//vector <int> answerCost;
//
//int n;
//
//bool isSatisfyMinimum(nutrient a){
//    return a.protein >= minimum.protein && a.carb >= minimum.carb && a.fat >= minimum.fat && a.vitamin >= minimum.vitamin;
//}
//
//void backtrack(int index, vector <int> result, nutrient nu){
//    nu = nu + list[index];
//    
//    if(!isSatisfyMinimum(nu)){
//        if(index == list.size() -1) ret;
//        if(maxCost < nu.cost){
//            nu = nu - list[index];
//            backtrack(index + 1, result, nu);
//        }
//        else{
//            result[index]++;
//            backtrack(index + 1, result, nu);
//            
//            nu = nu - list[index];
//            result[index]--;
//            backtrack(index + 1, result, nu);
//        }
//    }
//    else{
//        if(nu.cost < maxCost){
//            maxCost = nu.cost;
//            result[index]++;
//            
//            if(!answerCost.empty()){
//                if(answerCost.back() > maxCost){
//                    answer.clear();
//                    answerCost.clear();
//                }
//            }
//            
//            answer.push_back(result);
//            answerCost.push_back(maxCost);
//            result[index]--;
//        }
//        if(nu.cost == maxCost){
//            result[index]++;
//            answer.push_back(result);
//            answerCost.push_back(maxCost);
//            result[index]--;
//        }
//        
//        if(index == list.size() - 1) ret;
//        nu = nu - list[index];
//        backtrack(index + 1, result, nu);
//    }
//    
//}
//
//void input(){
//    ifstream inp("./3.inp");
//    int p, f, c, v, cost;
//    
//    inp >> n;
//    
//    inp >> minimum.protein >> minimum.fat >> minimum.carb >> minimum.vitamin;
//    minimum.cost = 0;
//    
//    
//    for(int i=0; i<n; i++){
//        int p, f, c, v, cost;
//        inp >> p >> f >> c >> v >> cost;
//        list.push_back(nutrient(p, f, c , v, cost));
//        maxCost += cost;
//    }
//    
//    inp.close();
//}
//
//void output(){
//    ofstream out("./diet.out");
//    
//    for(int i=0; i<n; i++)
//        if(answer.front()[i] != 0){
//            out << i + 1 << " ";
//            cout <<i + 1 << " ";
//        }
//    out << endl;
//    cout << endl;
//    
//    out.close();
//}
//
//int main(){
//    input();
//    vector <int> result(n, 0);
//    backtrack(0, result, nutrient(0, 0, 0, 0, 0));
//    output();
//    
//    
//    
//    return 0;
//}
