#include <bits/stdc++.h>
using namespace std;
long long p1Wins[21][21][10][10][2][4];
long long p2Wins[21][21][10][10][2][4];

pair<long long,long long> operator + (pair<long long,long long> a, pair<long long,long long> b)  {
  return make_pair(get<0>(a) + get<0>(b),get<1>(a) + get<1>(b));
}

pair<long long,long long> dp(int roll,int p1Score,int p2Score, int p1pos, int p2pos, int turn) {
  if (p1Wins[p1Score][p2Score][p1pos][p2pos][turn][roll] != -1) {
    return make_pair(p1Wins[p1Score][p2Score][p1pos][p2pos][turn][roll],p2Wins[p1Score][p2Score][p1pos][p2pos][turn][roll]);
  } else if (p1Score >= 21 && roll == 0) {
    return make_pair(1,0);
  } else if (p2Score >= 21 && roll == 0) {
    return make_pair(0,1);
  }
  else {
    if (roll == 3)  {
      int oldp1score = p1Score;
      int oldp2score = p2Score;      
      if (turn == 0) {
        p1Score += p1pos+1;
        pair<long long, long long> subResult = dp(0,p1Score,p2Score,p1pos,p2pos,(turn+1)%2);
        p1Wins[oldp1score][p2Score][p1pos][p2pos][turn][3] = get<0>(subResult);
        p2Wins[oldp1score][p2Score][p1pos][p2pos][turn][3] = get<1>(subResult);
        return subResult;
      } else {
        p2Score += p2pos+1;
        pair<long long, long long> subResult = dp(0,p1Score,p2Score,p1pos,p2pos,(turn+1)%2);
        p1Wins[p1Score][oldp2score][p1pos][p2pos][turn][3] = get<0>(subResult);
        p2Wins[p1Score][oldp2score][p1pos][p2pos][turn][3] = get<1>(subResult);
        return subResult;
      }
    }
    else {
      int oldp1pos = p1pos;
      int oldp2pos = p2pos;
      pair<long long,long long> total = make_pair(0,0);
      for (int diracRoll = 1;diracRoll<4;diracRoll++) {
        p1pos = oldp1pos;
        p2pos = oldp2pos;
        if (turn == 0) {
          p1pos += diracRoll;
          p1pos %= 10;
           total = total + dp(roll+1,p1Score,p2Score,p1pos,p2pos,turn);
        } else {
          p2pos += diracRoll;
          p2pos %= 10;
          total = total + dp(roll+1,p1Score,p2Score,p1pos,p2pos,turn);
        }
      } 
      p1Wins[p1Score][p2Score][oldp1pos][oldp2pos][turn][roll] = get<0>(total);
      p2Wins[p1Score][p2Score][oldp1pos][oldp2pos][turn][roll] = get<1>(total);
      return total;      
    }
  }
}

int main() {
  int p1;
  int p2;
  scanf("Player 1 starting position: %d\nPlayer 2 starting position: %d\n",&p1,&p2);
  --p1;
  --p2;

  for (int i=0;i<21;++i) {
    for (int j=0;j<21;++j) {
      for (int k=0;k<10;++k) {
        for (int l=0;l<10;++l) {
          for (int m=0;m<2;++m) {
            for (int n=0;n<4;++n) {
              p1Wins[i][j][k][l][m][n] = -1;
              p2Wins[i][j][k][l][m][n] = -1;
            }
          }
        }
      }
    }
  }

  cout << "Player 1 wins in " << get<0>(dp(0,0,0,p1,p2,0)) << " universes." << endl;
  cout << "Player 2 wins in " << get<1>(dp(0,0,0,p1,p2,0)) << " universes."<< endl;
}
