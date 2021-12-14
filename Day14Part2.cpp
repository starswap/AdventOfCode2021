#include <bits/stdc++.h>
using namespace std;

const int NUM_LEVELS = 40;

int main() {
  string startPattern;
  cin >> startPattern;
  
  unordered_map<string,int> ruleNos;
  unordered_map<string,char> rules;
  vector<long long> numChars(26,0);
  
  char a[2];
  char b;

  int ruleNo = 0;
  while (scanf("\n%s -> %c",a,&b) != EOF) {
    rules.insert(make_pair(string(a),b));
    ruleNos.insert(make_pair(string(a),ruleNo));
    ruleNo += 1;
  }

  int i;
  vector<long long> calls(ruleNo,0);

  for (i=0;i<startPattern.size()-1;i++) {
    calls[ruleNos[startPattern.substr(i,2)]] = 1;
    numChars[startPattern[i]-65] += 1;
  }
  numChars[startPattern[i]-65] = 1;

  for (int l=0;l<NUM_LEVELS;l++) {
    vector<long long> newCalls(ruleNo,0);
      
    for (const auto &[pattern,id] : ruleNos) {
      if (rules.count(pattern) == 0) continue;
      
      numChars[rules[pattern]-65] += calls[id];
      newCalls[ruleNos[string(1,pattern[0]) +rules[pattern]]] += calls[id];
      newCalls[ruleNos[string(1,rules[pattern]) + pattern[1]]] += calls[id];
    }
    calls = newCalls;
  }

  long long max = 0;
  long long min = 9223372036854775807; 
  for (long long item : numChars) {
    if (item > max)
      max = item;
    if (item < min && item != 0)
      min = item;
          
  } 
  cout << max - min << endl;
  return 0;
}
