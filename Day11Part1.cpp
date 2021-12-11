#include <bits/stdc++.h>
using namespace std;

int dr[] = {0,0,1,1,1,-1,-1,-1};
int dc[] = {1,-1,0,1,-1,0,1,-1};
const int MAX_STEPS = 100;
int w = 0,h = 0;

vector<vector<int>> octopi;
vector<vector<bool>> flashes;
int totalFlashes = 0;

void flash(int r, int c) {
  if (flashes[r][c]) 
    return;

  if (octopi[r][c] <= 9)
    return;

  ++totalFlashes;
  flashes[r][c] = true;
  for (int i=0;i<8;i++) {
    if (r+dr[i] < 0 || r+dr[i] >= h || c+dc[i] < 0 || c+dc[i] >= w)
      continue;

    octopi[r+dr[i]][c+dc[i]]++;
    flash(r+dr[i],c+dc[i]);
  }
}

void resetFlashed() {
  for (int r=0;r<h;r++) {
    for (int c=0;c<h;c++) {
      if (flashes[r][c])
        octopi[r][c] = 0;
    }
  }
}


int main() {
  string line;
  
  while (cin >> line) {
    octopi.push_back(vector<int>());
    w = 0;
    for (char c : line) {
      octopi[h].push_back(c-'0');
      ++w;
    }
    ++h;
  }

  for (int s=0;s<MAX_STEPS;++s) {
    flashes.assign(h,vector<bool>(w,false));
    for (int r=0;r<h;r++) {
      for (int c=0;c<w;c++) {
        ++octopi[r][c];
        flash(r,c);
      }
    }
    resetFlashed();
  }

  cout << "Total number of flashes: " << totalFlashes << endl;

} 
