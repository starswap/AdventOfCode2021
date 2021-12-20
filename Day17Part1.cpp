#include <bits/stdc++.h>
using namespace std;

int T(int x) {
  return (x*(x+1))/2;
}
float T_inverse(int x) {
  return ((-1+sqrt(1+8*x))/2);
}

int main() {
  int xMin,xMax;
  int yMin,yMax;
  scanf("target area: x=%d..%d, y=%d..%d",&xMin,&xMax,&yMin,&yMax);
  bool flag = false;
  for (int vy=1000;vy>=0;vy--) {

    if (ceil(T_inverse(T(vy) -yMax)) == floor(T_inverse(T(vy) - yMin))) {
      for (int vx=-1000;vx<1000;++vx) {  
        int t = min(static_cast<int>(ceil(T_inverse(T(vy) -yMax))+vy+1),vx);
        int xpos = t*vx-T(t-1);
        if (xpos >= xMin && xpos <= xMax) {
          flag = true;
          cout << T(vy) << endl;
          break;
        } 
      }
      if (flag)
        break;
    }
  }
  if (flag == false)
    cout << 0 << endl;

  return 0;
}
