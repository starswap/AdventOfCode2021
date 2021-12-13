#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int,int>> origamiPaper;

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
    cout << axis << "=" << posn << endl;
    if (axis == 'x') {
      foldOverX(posn,points);
    } else {
      foldOverY(posn,points);
    }
    removeDuplicates(points);
    cout << "Number of points after step " << i << " is " << points.size() << endl;
    ++i;
  }
 
  return 0;
}
