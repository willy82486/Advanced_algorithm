#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F first
#define S second
typedef pair<int, int> pii;


int fac[17] = {1, 1}, maxstatus = 0;
map<int, int> visit;
vector<int> goal = {5, 8, 6, 0, 7, 4, 2, 3, 1};
vector<int> op[17][15]; 

void print(vector<int> a){
	for(auto i: a)cout << i << ' ';
	cout << endl;
}

int khash(vector<int>a){
	int t, sum = 0, n = a.size();
	for(int i = 0; i < n; i++){
		t = 0;
		for(int j = i + 1; j < n; j++) t += (a[i] > a[j]);
		sum += t * fac[n - i - 1];
	}
	return sum;
}

int mdis(vector<int>a, vector<int>b){
	int dis = 0;
	for(int i = 0; i < a.size(); i++){
		int coorda, coordb;
		for(int j = 0; j < a.size(); j++){
			if(a[j] == i) coorda = j;
			if(b[j] == i) coordb = j;
			
		} 
		dis += abs(coorda / 3 - coordb / 3) + abs(coorda % 3 - coordb % 3);
	}
	return dis;
}

vector<int> rkhash(int num){
	vector<int>a, ans;
	for(int i = 0; i <= 8; i++)a.push_back(i);
	for(int i = 8; i > 0; i--){
		int r = num % fac[i], t = num / fac[i];
		num = r;
		ans.push_back(a[t]);
		a.erase(a.begin() + t);
	}
	ans.push_back(a[0]);
	return ans;
}

int DLS(vector<int>a, int parent, int coord, int limit){
	int ans = 0, ii;
	if(khash(goal) == khash(a))return 1;
	
	//recursive
	for(auto move: op[a.size()][coord]){
		vector<int>b = a;
		swap(b[coord], b[move]);
		if(khash(b) != parent && limit > 0){
			ans = max(ans, DLS(b, khash(a), move, limit - 1));
		}
		if(ans == 1) return 1;
	}
	return ans;
}

int IDS(vector<int>a, int coord){
	for(int limit = 0; limit < 30; limit++){
		cout << "Current limit is " << limit << endl;
		int result = DLS(a, khash(a), coord, limit);
		maxstatus = limit + 1;
		if(result == 1) return limit;
	}
	return -1;
}

int BFS(vector<int>a, int coord){
	// push the initial status
	queue<pii>status; status.push({khash(a), coord}); visit[khash(a)] = 1;
	//BFS algorithm
	while(!status.empty()){
		vector<int>top = rkhash(status.front().F);
		for(auto move: op[a.size()][status.front().S]){
			vector<int>b = top;
			swap(b[status.front().S], b[move]);
			if(!visit[khash(b)]){
				int tmpcoord = 0;
				status.push({khash(b), move});
				visit[khash(b)] = visit[khash(top)] + 1;
				if(khash(b) == khash(goal))return visit[khash(b)] - 1;
 			}
		}
		status.pop();
		maxstatus = max(maxstatus, (int)visit.size());
	}
	return -1;
}

int GBFS(vector<int>a, int coord){
	// the third default parameter is less<int>, then return the greatest in this queue.
	// thus, if want to return the smallest manhattan distance state, use the greater operator.
	priority_queue<pii, vector<pii>, greater<pii> > status;
	status.push({mdis(a, goal), khash(a)}); 
	visit[khash(a)] = 1;
	//BFS algorithm
	while(!status.empty()){
		int tmpcoord;
		vector<int>top = rkhash(status.top().S);
		for(int i = 0; i < top.size(); i++){
			if(top[i] == 0) tmpcoord = i;
		}
		print(top);
		for(auto move: op[top.size()][tmpcoord]){
			vector<int>b = top;
			swap(b[tmpcoord], b[move]);
			if(!visit[khash(b)]){
				int tmpcoord = 0;
				status.push({mdis(b, goal), khash(b)});
				visit[khash(b)] = visit[khash(top)] + 1;
				if(khash(b) == khash(goal))return visit[khash(b)] - 1;
 			}
		}
		status.pop();
		maxstatus = max(maxstatus, (int)visit.size());
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
		//note the checker only can check the 8-puzzle format
		if(b[0] || b[8] - 8 || tmpsum - 36){
			cout << "The puzzle format is not correct, plz re-enter the puzzle!\n";		
		}else{
			cout << "Choose a algorithm to execute the puzzle.\n";
			cout << "(1). Iterative-Deepening Search(IDS)\n";
			cout << "(2). Uniform-Cost Search\n";
			cout << "(3). Greedy Best-First Search\n";
			cout << "(4). A* Search\n";
			cout << "(5). Recursive Best-First Search(RBFS)\n";
			while(cin >> tc){
				//init before each algorithm
				int coord;
				maxstatus = -1;
				for(int i = 0; i < a.size(); i++){
					if(a[i] == 0) coord = i;
				}
				
				//each algorithm
				if(tc < 0 || tc > 5){
					cout << "The command is invaild, plz enter the correct command.";
					continue;
				}else if(tc == 1){
					int ans = IDS(a, coord);
					if(ans >= 0)cout << "Total moves: " << ans << endl;
					else cout << "The puzzle is not solvable!\n";
					cout << "The maximum number of states during the process is: " << maxstatus << endl;
					break;
				}else if(tc == 2){
					int ans = BFS(a, coord);
					if(ans > 0)cout << "Total moves: " << ans << endl;
					else cout << "The puzzle is not solvable!\n";
					cout << "The maximum number of states during the process is: " << maxstatus << endl;
					break;
				}else if(tc == 3){
					int ans = GBFS(a, coord);
					if(ans > 0)cout << "Total moves: " << ans << endl;
					else cout << "The puzzle is not solvable!\n";
					cout << "The maximum number of states during the process is: " << maxstatus << endl;
					break;
				}else if(tc == 4){
					cout << mdis(a, goal);
				}else{
				
				}
			}
		}
	}
}
