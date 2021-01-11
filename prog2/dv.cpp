#include <bits/stdc++.h>
#define int long long
using namespace std;


const int N = 1e4;
const int INF = 1e5;

//vector<vector<int>> adj(N, vector<int>(N,0));
vector<vector<int>> dist(N, vector<int>(N,INF));
vector<vector<int>> nexthop(N, vector<int>(N,INF));

int32_t main(){
	int n;
	cout << "Enter number of nodes: " << endl;
	cin >> n;
	cout << "Enter Adjaceny matrix:\n";
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			cin >> dist[i][j];
			nexthop[i][j] = j;
		}
	}
	for(int i=0; i<n; i++){
		dist[i][i] = 0;
		nexthop[i][i] = i;
	}
		
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			for(int k=0; k<n; ++k){
				if(dist[i][k] + dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
					nexthop[i][j] = k;
				}
			}
		}
	}
	for(int i=0; i<n; ++i){
		cout << "Final config for router:" << i << endl;
		cout << "Dest\t" << "Cost\t" << "Next hop"<< endl;
		for(int j=0; j<n; ++j){
			cout << j << "\t" << dist[i][j] << "\t" << nexthop[i][j] << endl;
		}
		cout << endl;
	}
		
}
