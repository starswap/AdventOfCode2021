#include <bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>> &AL,int visitedMask,int u,int start,int end,unordered_set<int> &smallCaves,bool visitedTwice) {
  if (smallCaves.count(u) == 1 && ((visitedMask & (1<<u)) == 1<<u)) {
    if (visitedTwice || u == start || u == end) {//small and already visited
      return 0;
    } else {
      if (u == end) 
        return 1;

      int total = 0;
      for (auto v : AL[u]) {
        total += dfs(AL,visitedMask,v,start,end,smallCaves,true);
      }
      return total;
    }
  }
  
  if (u == end) 
    return 1;

  int total = 0;
  for (auto v : AL[u]) {
    total += dfs(AL,visitedMask | (1<<u),v,start,end,smallCaves,visitedTwice);
  }
  return total;
}


int main() {
  char a[50];
  char b[50];

  unordered_map<string,int> intMapping;
  vector<pair<string,string>> EL;
  unordered_set<int> smallCaves;
  int c = 0;
  while (scanf("%[^-\n]-%[^-\n]\n",a,b) != EOF) {
    EL.push_back(make_pair(string(a),string(b)));
    if (intMapping.count(string(a)) == 0) {
      intMapping.insert(make_pair(string(a),c));
      string upperString = string(a);
      for_each(upperString.begin(),upperString.end(), [](char & c){c = ::toupper(c);});  
      if (upperString != string(a)) {
        smallCaves.insert(c);
      }
      c++;
    }
    if (intMapping.count(string(b)) == 0) {
      intMapping.insert(make_pair(string(b),c));
      string upperString = string(b);
      for_each(upperString.begin(),upperString.end(), [](char & c){c = ::toupper(c);});  
      if (upperString != string(b)) {
        smallCaves.insert(c);
      }

      c++;
    }
  }
  
  vector<vector<int>> AL(c,vector<int>());
  int start = intMapping["start"];
  int end = intMapping["end"];
  for (const auto &[s,e] : EL) {
    AL[intMapping[s]].push_back(intMapping[e]);
    AL[intMapping[e]].push_back(intMapping[s]);
  }

  cout << dfs(AL,0,start,start,end,smallCaves,false) << endl;

  return 0;
}
