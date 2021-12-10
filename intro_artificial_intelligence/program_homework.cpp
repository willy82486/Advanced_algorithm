#include<bits/stdc++.h>
using namespace std;
#define int long long

int fac[17] = {1, 1}, goalnum;
map<int, int> visit;
vector<int> goal = {5,8,6,0,7,4,2,3,1};
vector<int> op[17][15]; 

int khash(vector<int>a){
	int t, sum = 0, n = a.size();
	for(int i = 0; i < n; i++){
		t = 0;
		for(int j = i + 1; j < n; j++) t += (a[i] > a[j]);
		sum += t * fac[n - i - 1];
	}
	return sum;
}

int DLS(vector<int>a, int coord, int limit){
	cout << khash(a) << ' ' << goalnum<< endl;
	if(limit == -1) return -1;
	else if(khash(a) == goalnum) return limit;
	else{
		visit[khash(a)] = 1;
		int ans = 0;
		for(auto move: op[a.size()][coord]){
			cout << coord << ' ' << move << endl; 
			vector<int>b = a;
			swap(b[coord], b[move]);
			if(!visit[khash(b)]){
				ans |= DLS(b, move, limit - 1);
			}
			if(ans == 1) return 1;
		}
	}
}

int IDS(vector<int>a, int coord){
	for(int limit = 0; limit < 30; limit++){
		int result = DLS(a, coord, limit);
		if(result != -1) return result;
	}
	return -1;
}


int32_t main(){
	// init
	int tc;
	vector<int>a(9), b;
	for(int i = 2; i < 16; i++) fac[i] = fac[i-1] * i;
	//opeartions for 8-puzzles
	op[9][0] = {1, 3};
	op[9][1] = {0, 2, 4};
	op[9][2] = {1, 5};
	op[9][3] = {0, 4, 6};
	op[9][4] = {1, 3, 5, 7};
	op[9][5] = {2, 4, 8};
	op[9][6] = {3, 7};
	op[9][7] = {4, 6, 8};
	op[9][8] = {5, 7};
	//opeartions for 15-puzzles
	op[16][0] = {1, 4};
	op[16][1] = {0, 2, 5};
	op[16][2] = {1, 3, 6};
	op[16][3] = {2, 7};
	op[16][4] = {0, 5, 8};
	op[16][5] = {1, 4, 6, 9};
	op[16][6] = {2, 5, 7, 10};
	op[16][7] = {3, 6, 11};
	op[16][8] = {4, 9, 12};
	op[16][9] = {5, 8, 10, 13};
	op[16][10] = {6, 9, 11, 14};
	op[16][11] = {7, 10, 15};
	op[16][12] = {8, 13};
	op[16][13] = {9, 12, 14};
	op[16][14] = {10, 13, 15};
	op[16][15] = {11, 14};
	
	// main UI
	while(cin >> a[0]){
		visit.clear();
		for(int i = 1; i < 9; i++) cin >> a[i];
		b = a, sort(b.begin(), b.end());
		int tmpsum = 0;
		for(auto i: b)tmpsum += i;
		if(b[0] || b[8] - 8 || tmpsum -36){
			cout << "The puzzle format is not correct, plz re-enter the puzzle!\n";		
		}else{
			cout << "Choose a algorithm to execute the puzzle.\n";
			cout << "(1). Iterative-Deepening Search(IDS)\n";
			cout << "(2). Uniform-Cost Search\n";
			cout << "(3). Greedy Best-First Search\n";
			cout << "(4). A* Search\n";
			cout << "(5). Recursive Best-First Search(RBFS)\n";
			while(cin >> tc){
				goalnum = khash(goal);
				visit[khash(a)] = 1;
				
				if(tc < 0 || tc > 5){
					cout << "The command is invaild, plz enter the correct command.";
					continue;
				}
				int coord;
				for(int i = 0; i < a.size(); i++){
					if(a[i] == 0) coord = i;
				}
				if(tc == 1){
					cout << "Total moves: " << IDS(a, coord) << endl;
					break;
				}
			}
		}
	}
}
