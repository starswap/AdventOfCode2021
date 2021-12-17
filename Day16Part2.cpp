#include <bits/stdc++.h>
using namespace std;

//Ascii-'0' to hex
const int hexConv[] = {0,1,10,11,100,101,110,111,1000,1001,0,0,0,0,0,0,0,1010,1011,1100,1101,1110,1111};
const int MAX_BITS = 6000; //max size of my bitset

//Equivalent of Haskell foldl
template <typename T,typename A>
A foldl(vector<T> list,A startingAcc,A (*f)(A,T)) { //
  for (T i : list) {
    startingAcc = f(startingAcc,i);
  }
  return startingAcc;
}

//Define functions to work specifically on long long
long long plusn(long long a,long long b) {return a+b;}
long long times(long long a,long long b) {return a*b;}
long long minr(long long a,long long b) {return min(a,b);}
long long maxr(long long a,long long b) {return max(a,b);}

//One for each type of packet
long long summing(vector<long long> vals) {return foldl(vals,0LL,plusn);} 
long long product(vector<long long> vals) {return foldl(vals,1LL,times);} 
long long minimum(vector<long long> vals) {return foldl(vals,LONG_LONG_MAX,minr);} 
long long maximum(vector<long long> vals) {return foldl(vals,0LL,maxr);} 
long long greatern(vector<long long> vals) {return vals[0] > vals[1];}
long long lessn(vector<long long> vals) {return vals[0] < vals[1];}
long long equal(vector<long long> vals) {return vals[0] == vals[1];}

//start with the pointer at the maximum index (leftmost in c++ bitset) and work rightwards
int ptr = MAX_BITS-1;

//Recursively process packets in the message - lengthCap tells us when we need to stop processing because there is no more useful data (only padding) after this point or the packet ends before then as it has a known length from the length type with 15 bits
long long processPacket(bitset<MAX_BITS> &message,int lengthCap) {

  if (ptr <= lengthCap) //No more processing is to be carried out
    return -1;

  //Compute version and type ids
  long long version = 4*message[ptr]+2*message[ptr-1]+message[ptr-2];
  ptr -= 3;
  long long typeId = 4*message[ptr]+2*message[ptr-1]+message[ptr-2];
  ptr -= 3;  
  
  long long subPackets = 0; //number of subPackets or totel length depending on length type id
  switch (typeId) { //check whether we have a literal value or an operator packet
    case 4:  { //literal value
      long long litVal = 0; //stores the literal value
      
      //All 5-blocks until terminal
      while (message[ptr] != 0) {
        --ptr;
        litVal = litVal<<4; //shifting by 4 as in part 1
        litVal += 8*message[ptr]+4*message[ptr-1]+2*message[ptr-2]+1*message[ptr-3];
        ptr -= 4;
      }
      
      //once more for terminal
      --ptr;
      litVal = litVal<<4;
      litVal += 8*message[ptr]+4*message[ptr-1]+2*message[ptr-2]+message[ptr-3];
      ptr -= 4;  
      return litVal;
    }
    default : {
      vector<long long> allSubPackets; //values of all subpackets in this packet
      if (message[ptr] == 0) { //next 15
        ptr -= 1;
        for (int b=14;b>=0;--b) {
          subPackets += (1<<b)*message[ptr]; //length of all subpackets
          --ptr;
        }
        long long nextPacket = 0;
        int cap = ptr-subPackets; //new length cap prevents evaluation further than the defined length
        while (nextPacket != -1) { //until we exceed this cap
          nextPacket = processPacket(message,cap); //get another packet
          if (nextPacket != -1) //valid so save it
            allSubPackets.push_back(nextPacket); 
        }
      }  
      else if (message[ptr] == 1) { //next 11
        ptr -= 1;
        for (int b=10;b>=0;--b) {
          subPackets += (1<<b)*message[ptr]; //total number of subpackets
          --ptr;
        }
        for (int i=0;i<subPackets;i++){ //grab each one
          long long nextPacket = processPacket(message,lengthCap);
          if (nextPacket != -1) 
            allSubPackets.push_back(nextPacket); 
        }         
      }
      switch (typeId) { //depending on the operator type, evaluate the result from the subpackets list
        case 0 : return summing(allSubPackets);
        case 1 : return product(allSubPackets);
        case 2 : return minimum(allSubPackets);
        case 3 : return maximum(allSubPackets);
        case 5 : return greatern(allSubPackets);
        case 6 : return lessn(allSubPackets);
        case 7 : return equal(allSubPackets);
      }      
    }
  }
}


int main () {
  //Represent input
  bitset<MAX_BITS> messageBits;
  string input;
  cin >> input;
  int b = MAX_BITS-1;
  for (char c : input) {
    int nextNibble = hexConv[c-'0'];
    messageBits[b--] = nextNibble/1000;
    messageBits[b--] = (nextNibble-1000*(nextNibble/1000))/100;
    messageBits[b--] = (nextNibble-100*(nextNibble/100))/10;
    messageBits[b--] = (nextNibble-10*(nextNibble/10));
  }
  
  //b is the lengthCap - tells us where the boundary between message and padding zeros lies.
  while (messageBits[b] == 0) {
    ++b;
  }
  --b;

  cout << processPacket(messageBits,b) << endl;
  
  return 0;
}
