#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1,1,0,0};
int dc[] = {0,0,1,-1};

int main () {
  string line;
  vector<vector<int>> grid;
  int i = 0,j = 0;
  while (cin >> line) {
    j = 0;
    grid.push_back(vector<int>());
    for (char c : line) {
      grid[i].push_back(c-'0'); //integer conversion techincally redundant
      j++;
    }
    ++i;
  }
  int total = 0;
  for (int p=0;p<i;p++) {
    for (int q=0;q<j;q++) {
      bool flag = true;
      for (int d = 0;d<4;d++) {
        if ((-1 < p+dr[d]) && (p+dr[d] < i) && (-1 < q+dc[d]) && (q+dc[d] < j) && grid[p+dr[d]][q+dc[d]] <= grid[p][q]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        total += 1;
        total += grid[p][q];
      }
    }
  }
  cout << total << endl;

}
