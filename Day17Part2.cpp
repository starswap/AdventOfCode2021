#include <bits/stdc++.h>
using namespace std;

int T(int x) {
  if (x == 0) return 0;
  return (x*(x+1))/2;
}
float T_inverse(int x) {
  return ((-1+sqrt(1+8*x))/2);
}

int main() {
  int xMin,xMax;
  int yMin,yMax;
  scanf("target area: x=%d..%d, y=%d..%d",&xMin,&xMax,&yMin,&yMax);
  int count = 0;
  for (int vy=1000;vy>-1000;vy--) {
    for (int vx=0;vx<1000;++vx) {  
      int xpos = 0;
      int ypos = 0;
      int vvx = vx;
      int vvy = vy;
      while (!(xpos > xMax || ypos < yMin)) {
        xpos += vvx;
        ypos += vvy;
        vvy -= 1;
        if (vvx > 0)
          vvx--;
        else if (vvx < 0)
          vvx++;
        if (xpos <= xMax && xpos >= xMin && ypos <= yMax && ypos >= yMin) {
          ++count;
          break;
        }
        if (xpos < xMin && vvx == 0)
          break; 
      }
    }
  }
  cout << count << endl;

  return 0;
}
