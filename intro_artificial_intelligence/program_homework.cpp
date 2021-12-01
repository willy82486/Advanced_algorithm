#include<bits/stdc++.h>
using namespace std;

void IDS(vector<int>a){
	
}

int main(){
	int tc;
	vector<int>a(9);
	while(cin >> a[0]){
		for(int i = 1; i < 9; i++) cin >> a[i];
		sort(a.begin(), a.end());
		for(auto i: a)cout << i << ' ';
		cout << endl;
		if(a[0] || a[8] - 8){
			cout << "The puzzle format is not correct, plz reenter the puzzle!\n";		
		}
	}
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
