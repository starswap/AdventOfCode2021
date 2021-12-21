#include <bits/stdc++.h>
using namespace std;

int main() {
  int p1;
  int p2;
  scanf("Player 1 starting position: %d\nPlayer 2 starting position: %d\n",&p1,&p2);
  int die=1;
  int p1Score = 0;
  int p2Score = 0;
  bool playerOne = true;
  while (!(p1Score >= 1000 || p2Score >= 1000)) {
    if (playerOne) {
      p1 = (p1+3+3*(die%100)) % 10;
      if (p1 == 0)
        p1 = 10;
      p1Score += p1;
    } 
    else {
      p2 = (p2+3+3*(die%100)) % 10;
      if (p2 == 0)
        p2 = 10;    
      p2Score += p2;
    }
    die += 3;
    playerOne = !playerOne;
  }
  cout << (die-1)*(playerOne ? p1Score : p2Score) << endl;
}
