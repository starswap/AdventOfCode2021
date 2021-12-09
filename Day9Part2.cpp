#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1,1,0,0};
int dc[] = {0,0,1,-1};

vector<vector<bool>> visited;
int dfs(vector<vector<int>> &grid,int r,int c,int maxRows,int maxCols) {
  if (visited[r][c]) return 0;
  visited[r][c] = true;
  if (grid[r][c] == 9) return 0;

  int total = 1;
  for (int d = 0;d<4;d++) {
    if ((-1 < r+dr[d]) && (r+dr[d] < maxRows) && (-1 < c+dc[d]) && (c+dc[d] < maxCols)) {
      total += dfs(grid,r+dr[d],c+dc[d],maxRows,maxCols);
    }
  }    
  return total;
}

int main () {
  string line;
  vector<vector<int>> grid;
  int i = 0,j = 0;
  while (cin >> line) {
    j = 0;
    grid.push_back(vector<int>());
    for (char c : line) {
      grid[i].push_back(c-'0');
      j++;
    }
    ++i;
  }
  visited.assign(i,vector<bool>(j,false));

  vector<int> components;
  for (int p=0;p<i;p++) {
    for (int q=0;q<j;q++) {
      int size = dfs(grid,p,q,i,j);
      if (size != 0) {
        components.push_back(size);
      }
    }
  }
  sort(components.rbegin(),components.rend());
  cout << components[0] * components[1] * components[2] << endl;
}
