#include <bits/stdc++.h>
using namespace std;
int grid[101][101][101];

int main() {
  int xMin,xMax,yMin,yMax,zMin,zMax;
  char direction[4];
  while (scanf("%[^ ] x=%d..%d,y=%d..%d,z=%d..%d\n",direction,&xMin,&xMax,&yMin,&yMax,&zMin,&zMax) != EOF) {
    for (int x=xMin;x<=xMax;++x)
      for (int y=yMin;y<=yMax;++y)
        for (int z=zMin;z<=zMax;++z)
          grid[x+50][y+50][z+50] = (strcmp(direction,"on") == 0) ? 1 : 0;
  }
  int count = 0;
  for (int x=0;x<=100;++x)
    for (int y=0;y<=100;++y)
      for (int z=0;z<=100;++z)  
        count += grid[x][y][z];
  cout << count << endl;
  return 0;
}
