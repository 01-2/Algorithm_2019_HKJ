#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int p[] = {-1, -1, -2, -2};
int q[] = {-1, -2, -1, -2};
int row, col;

bool isRange(int r, int c) {
	if ( r >= 0 && r < row && c >= 0 && c < col )
		return true;
	return false;
}

class loc {
	public:
		int r, c;
		string str;
		loc() {
			r = 0;
			c = 0;
			str = "";
		}
		loc (int _r, int _c, string _str) {
			r = _r;
			c = _c;
			str = _str;
		}
};

void ClearQueue(queue<loc> &que)
{
    queue<loc> empty;
    swap(que, empty);
}

int main() {
	ifstream ifs("dna.inp");
	ofstream ofs("dna.out");
	string str_one, str_two;
	ifs >> str_one >> str_two;
	row = str_one.length();
	col = str_two.length();
	vector< vector<int> > maps;
	maps.assign(row, vector<int>(col, 0)); // Make table which is size 'row * col' for running DP 
	for ( int r = 0; r < row; r++ )
		for ( int c = 0; c < col; c++ )
			if ( str_one[r] == str_two[c] ) { // In each location that the two characters are same, Find the maximum value.
				maps[r][c] = 1;	
				for ( int i = 0; i < 4; i++ )
					if ( isRange(r+p[i], c+q[i]) )
						maps[r][c] = max(maps[r][c], maps[r+p[i]][c+q[i]]+1);
			}
	int max = 0;	// Find all of the location max value is stored.
	queue<loc> que;
	for ( int r = 0; r < row; r++ ) {
		for ( int c = 0; c < col; c++ ) {
			if ( max < maps[r][c] ) {
				ClearQueue(que);
				que.push(loc(r, c, string(1, str_one[r])));
				max = maps[r][c];
			} else if ( max == maps[r][c] )
				que.push(loc(r, c, string(1, str_one[r])));
		}
	}
	string result = "";
	while ( !que.empty() ) {	// In each elements of Queue, Make 'result' by comparing other words which can make itself.
		loc tmp = que.front();	que.pop();
		for ( int i = 0; i < 4; i++ ) {
			int r = tmp.r + p[i];
			int c = tmp.c + q[i];
			if ( isRange(r, c) && maps[r][c] > 0 && maps[tmp.r][tmp.c] == maps[r][c]+1 ) {
				string com = string(1, str_one[r])+tmp.str;
				que.push(loc(r, c, com));
				if ( result.length() < com.length() )
					result = com;
				else if ( result.length() == com.length() )
					result = result < com ? result : com;
			}
		}
	}
	ofs << result;
	ifs.close();
	ofs.close();
	return 0;
}
