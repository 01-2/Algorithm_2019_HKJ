#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define INFILE_NAME     "polygon.inp"
#define OUTFILE_NAME    "polygon.out"

#define PI  3.14159265359

using namespace std;

class pos{
public:
    int x;
    int y;
    pos(){ x = 0; y = 0; }
    pos(int _x, int _y){ x = _x; y = _y; }
};

int total_num = 0, concave_count = 0;
bool intersect_flag = false;
vector<pos> pos_list;

void input_data(){
    int _x = 0; int _y = 0;
    ifstream inFile(INFILE_NAME);
    inFile >> total_num;
    for(int i = 0; i < total_num; i++){
        inFile >> _x >> _y;
        pos_list.push_back(pos(_x, _y));
    }
    _x = pos_list[0].x;
    _y = pos_list[0].y;
    pos_list.push_back(pos(_x, _y));
    
    _x = pos_list[1].x;
    _y = pos_list[1].y;
    pos_list.push_back(pos(_x, _y));
    inFile.close();
}
void output_data(){
    ofstream outFile(OUTFILE_NAME);
    if(concave_count > 0){
        outFile << "Concave " << concave_count << endl;
        cout << "Concave " << concave_count << endl;
    }
    else if(intersect_flag){
        outFile << "None" << endl;
        cout << "None" << endl;
    }
    else{
        outFile << "Convex" << endl;
        cout << "Convex" << endl;
    }

    outFile.close();
}

int ccw(pos p1, pos p2, pos p3){
    int temp = (p1.x * p2.y) + (p2.x * p3.y) + (p3.x * p1.y);
    temp = temp - (p1.y * p2.x) - (p2.y * p3.x) - (p3.y * p1.x);
    if(temp > 0) return 1;          // rotate counter-cw
    else if(temp < 0) return -1;    // rotate cw
    else return 0;                  // inline
}

bool check_intersect(pos p1, pos p2, pos p3, pos p4){
    // http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
    double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // d = 0 -> no intersection
    if(d == 0) return false;
    
    double pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;
    
    if(x <= min(x1, x2) || x >= max(x1, x2) ||
       x <= min(x3, x4) || x >= max(x3, x4)) return false;
    if(y <= min(y1, y2) || y >= max(y1, y2) ||
       y <= min(y3, y4) || y >= max(y3, y4)) return false;
    
    return true;
}
void none_check(){
    for(int i = 0; i < pos_list.size() - 2; i++){ // line_1 loop
        for(int j = i + 2; j < pos_list.size() - 2; j++){ // line_2 loop
            intersect_flag = check_intersect(pos_list[i], pos_list[i+1],
                                             pos_list[j], pos_list[j+1]);
            if(intersect_flag == true) return;
        }
    }
}

double get_angle(pos p1, pos p2, pos p3){
    // v1 = (x1-x2, y1-y2), v2 = (x3-x2, y3-y2)
    int flag = 0;
    double angle =
    acos(((p1.x - p2.x) * (p3.x - p2.x) + (p1.y - p2.y) * (p3.y - p2.y))
         / (sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2))
            * sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2))));
    
    flag = ccw(p1, p2, p3);
    
    if(flag < 0) angle = angle * (180 / PI);
    else if(flag > 0) angle = 360 - (angle * (180 / PI));
    else angle = 0;
    
    return angle;
}
void check_concave(){
    double temp_angle;
    for(int i = 0; i < pos_list.size()-2; i++){
        temp_angle = get_angle(pos_list[i], pos_list[i+1], pos_list[i+2]);
        cout << temp_angle << endl;
        if(temp_angle > 180) concave_count++;
    }
}
int main(int argc, const char * argv[]) {
    input_data();
    none_check();
    if(!intersect_flag) check_concave();
    output_data();
    return 0;
}
