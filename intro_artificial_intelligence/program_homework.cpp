#include<bits/stdc++.h>
using namespace std;
#define int long long

int fac[17] = {1, 1};
map<int, int>visit;

int khash(vector<int>a){
	int t, sum = 0, n = a.size();
	for(int i = 0; i < n; i++){
		t = 0;
		for(int j = i + 1; j < n; j++) t += (a[i] > a[j]);
		sum += t * fac[n - i - 1];
	}
	return sum;
}

int DLS(vector<int>a, int limit){
	if(limit == -1) return -1;
	
}

int IDS(vector<int>a){
	for(int limit = 1; limit < 30; limit++){
		int result = DLS(a, limit);
		if(result != -1) return result;
	}
	return -1;
}


int32_t main(){
	// init
	int tc;
	vector<int>a(9), b;
	for(int i = 2; i < 16; i++) fac[i] = fac[i-1] * i;
	
	// main UI
	while(cin >> a[0]){
		for(int i = 1; i < 9; i++) cin >> a[i];
		b = a, sort(b.begin(), b.end());
		int tmpsum = 0;
		for(auto i: b)cout << i << ' ', tmpsum += i;
		cout << endl;
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
				if(tc < 0 || tc > 5){
					cout << "The command is invaild, plz enter the correct command.";
					continue;
				}
				if(tc == 1){
					vector<int> goal = {5,8,6,0,7,4,2,3,1};
					IDS(goal);
				}
			}
		}
	}
}
