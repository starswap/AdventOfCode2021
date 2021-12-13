#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int,int>> origamiPaper;

ostream& operator << (ostream& o, origamiPaper p) {
  set<pair<int,int>> s(p.begin(),p.end());
  for (int y=0;y<20;y++) {
    for (int x=0;x<200;x++) {
      if (s.count(make_pair(x,y)) > 0) {
        o << '#';
      } else {
        o << '.';
      }
    }
    o << '\n';
  }
  return o;
} 

void foldOverX(int posn,origamiPaper &points) {
  for (auto &[x,y] : points) {
    x = x-2*max(0,x-posn);
  }
}

void foldOverY(int posn, origamiPaper &points) {
  for (auto &[x,y] : points) {
    y = y-2*max(0,y-posn);
  }
}

void removeDuplicates(origamiPaper &points) {
  sort(points.begin(), points.end());
  points.erase(unique(points.begin(), points.end()),points.end());
}

int main() {
  int a;
  int b;
  origamiPaper points;
  while (scanf("%d,%d\n",&a,&b) != 0) {
    points.push_back(make_pair(a,b));
  }
  char axis;
  int posn;
  int i = 1;
  while (scanf("fold along %c=%d\n",&axis,&posn) != EOF) {
    if (axis == 'x') {
      foldOverX(posn,points);
    } else {
      foldOverY(posn,points);
    }
    removeDuplicates(points);
    ++i;
  }
  cout << points << endl;
 
  return 0;
}
