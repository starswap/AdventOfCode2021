#include <bits/stdc++.h>
using namespace std;

const int dr[] = {0,1,0,-1};
const int dc[] = {1,0,-1,0};
const int INF = 1e9;

int dijkstra(vector<vector<int>> &grid,int rt,int ct) {
  vector<vector<int>> upToDateCosts(rt,vector<int>(ct,INF));
  priority_queue<tuple<int,int,int>> pq;  //-cost,x,y;
  pq.push(make_tuple(0,0,0));
  upToDateCosts[0][0] = 0;

  while (!pq.empty()) {
    auto [cost,r,c] = pq.top(); pq.pop();
    cost = -cost;

    if (cost != upToDateCosts[r][c]) continue;
    //if (r==rt-1 && c==ct-1) break;
    for (int i=0;i<4;++i) {      
      if (r+dr[i] > -1 && r+dr[i] < rt && c+dc[i] > -1 && c+dc[i] < ct) {
        int newCost = cost+grid[r+dr[i]][c+dc[i]]; 
        if (newCost < upToDateCosts[r+dr[i]][c+dc[i]]) {
          upToDateCosts[r+dr[i]][c+dc[i]] = newCost;
          pq.push(make_tuple(-newCost,r+dr[i],c+dc[i]));
        }
      }
    }
  }
  return upToDateCosts[rt-1][ct-1];
}


int main() {
  int rt = 0;
  int ct = 0;
  string row;
  vector<vector<int>> costs;
  while (cin >> row) {
    costs.push_back(vector<int>());
    ct = 0;
    for (char c : row) {
      costs[rt].push_back(c-'0');  
      ++ct;
    }
    ++rt;
  }
  cout << dijkstra(costs,rt,ct) << endl;
  return 0;
}
