#include <bits/stdc++.h>
using namespace std;

const int STEPS = 2; //Part 1
//const int STEPS = 50;  //Part 2
const int dr[] = {-1,-1,-1,0,0,0,1,1,1};
const int dc[] = {-1,0,1,-1,0,1,-1,0,1};
char allOthers = '.';

ostream& operator << (ostream& o, vector<vector<char>> v) {
  for (vector<char> sv : v) {
    for (char c : sv) {
      o << c;
    }
    o << endl;
  }
  return o;
}


char getValue(int r,int c,vector<vector<char>> &pixels) {
  if (r >= 0 && r < pixels.size() && c >= 0 && c < pixels.size())
    return pixels[r][c];
  else
    return allOthers;
}


string rules;
void applyStep(vector<vector<char>> &pixels) {
  vector<vector<char>> newPixels = pixels;
  for (int r=0;r<pixels.size();++r) {
    for (int c=0;c<pixels.size();++c) {
      int mult = 256;
      int total = 0;
      for (int i=0;i<9;i++) {
        if (getValue(r+dr[i],c+dc[i],pixels) == '#')
          total += mult;
        mult /= 2;
      }
      newPixels[r][c] = rules[total];
    }
  }
  if (allOthers == '#')
    allOthers = rules[511];
  else
    allOthers = rules[0];
  pixels = newPixels;
}

int lightPixels(vector<vector<char>> v) {
  int count = 0;
  for (vector<char> sv : v) {
    for (char c : sv) {
      if (c == '#')
        ++count;
    }
  }
  return count;
}

int main() {
  cin >> rules;
  string firstLine;
  cin >> firstLine;

  int n = firstLine.size();
  vector<vector<char>> pixels(n+2*(STEPS+1),vector<char>(n+2*(STEPS+1),'.'));
  for (int r=0;r<n;++r) {
    for (int c=0;c<n;++c) {
      pixels[r+STEPS][c+STEPS] = firstLine[c];
    } 
    cin >> firstLine;
  }
  //cout << pixels << endl;
  for (int s=0;s<STEPS;++s) {
    applyStep(pixels);
  //  cout << pixels << endl;
  }
  cout << lightPixels(pixels) << endl;


  return 0;
} 
