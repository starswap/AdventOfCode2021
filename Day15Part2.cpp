#include <bits/stdc++.h>
using namespace std;

const int dr[] = {0,1,0,-1};
const int dc[] = {1,0,-1,0};
const int INF = 1e9;
const int MAX_GRID_MULTIPLES = 5;

int getCost(vector<vector<int>> &grid,int r, int c,int rt,int ct) {
  int qr = r / rt;
  int rr = r % rt;
  int qc = c / ct;
  int rc = c % ct;
  int score = (grid[rr][rc] + qr + qc) % 9;
  if (score == 0)
    score = 9;
  return score;
}

int dijkstra(vector<vector<int>> &grid,int rt,int ct) {
  vector<vector<int>> upToDateCosts(rt*MAX_GRID_MULTIPLES,vector<int>(ct*MAX_GRID_MULTIPLES,INF));
  priority_queue<tuple<int,int,int>> pq;  //-cost,x,y;
  pq.push(make_tuple(0,0,0));
  upToDateCosts[0][0] = 0;

  while (!pq.empty()) {
    auto [cost,r,c] = pq.top(); pq.pop();
    cost = -cost;

    if (cost != upToDateCosts[r][c]) continue;
    for (int i=0;i<4;++i) {      
      if (r+dr[i] > -1 && r+dr[i] <rt*MAX_GRID_MULTIPLES && c+dc[i] > -1 && c+dc[i] < ct*MAX_GRID_MULTIPLES) {
        int newCost = cost+getCost(grid,r+dr[i],c+dc[i],rt,ct); 
        if (newCost < upToDateCosts[r+dr[i]][c+dc[i]]) {
          upToDateCosts[r+dr[i]][c+dc[i]] = newCost;
          pq.push(make_tuple(-newCost,r+dr[i],c+dc[i]));
        }
      }
    }
  }
  return upToDateCosts[rt*MAX_GRID_MULTIPLES-1][ct*MAX_GRID_MULTIPLES-1];
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
