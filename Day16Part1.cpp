#include <bits/stdc++.h>
using namespace std;

const int hexConv[] = {0,1,10,11,100,101,110,111,1000,1001,0,0,0,0,0,0,0,1010,1011,1100,1101,1110,1111}; //Ascii to bits.
const int MAX_BITS = 6000; //size of bitset

int ptr = MAX_BITS-1; //indexed from 0 but start at bit with highest index so that when we print the bitset it appears left to right as in the examples


int processPacket(bitset<MAX_BITS> &message,int lengthCap) {
  
  if (ptr <= lengthCap) //base case - ignore all 0s after the end of the data
    return 0;
  
  //Obtain version and type IDs
  int version = 4*message[ptr]+2*message[ptr-1]+message[ptr-2];
  ptr -= 3;
  int typeId = 4*message[ptr]+2*message[ptr-1]+message[ptr-2];
  ptr -= 3;  
  
  int subPackets = 0; //will store the number of subpackets contained within this packet

  switch (typeId) { //Depending on what the type of the packet is, we should process it in different ways
    case 4:  { //literal value packet
      int litVal = 0; //will store the literal
      
      //All 5-blocks until terminal
      while (message[ptr] != 0) {
        --ptr;
        litVal = litVal<<4; //previous literal value was not the last block so make binary space for this block.
        litVal += 8*message[ptr]+4*message[ptr-1]+2*message[ptr-2]+2*message[ptr-3]; //the shifting above means that using these place values of 8,4,2,1 is always right
        ptr -= 4; //advance the pointer (which is a global variable)
      }
      
      //once more for terminal block of 5
      --ptr;
      litVal = litVal<<4;
      litVal += 8*message[ptr]+4*message[ptr-1]+2*message[ptr-2]+2*message[ptr-3];
      ptr -= 4;
      
      //In partA we want the version number sum over all packets. If there is more to the message after this packet we will need to add that on. 
      return version+processPacket(message,lengthCap);
    }
    default : { //Not a literal value packet
      //Check length type IDs
      if (message[ptr] == 0) { //next 15
        ptr -= 1;
        for (int b=14;b>=0;--b) { //use the next 15 bits to calculate how many subpackets are contained within this packet
          subPackets += (1<<b)*message[ptr]; 
          --ptr;
        }
      }  
      else if (message[ptr] == 1) { //next 11 bits
        ptr -= 1;
        for (int b=10;b>=0;--b) { //use the next 11 bits to calculate how many subpackets are contained within this packet
          subPackets += (1<<b)*message[ptr]; 
          --ptr;
        }
      }
    }
  }

  //If we get here subpackets are present. Sum versions for all subpackets for part1, although clearly for part2 it will be necessary to do something difference with these.
  int total = version;
  for (int i=0;i<subPackets;i++){
    total += processPacket(message,lengthCap); 
  } 
  return total; //total version numbers
}


int main () {
  bitset<MAX_BITS> messageBits;
  string input;
  cin >> input;
  int b = MAX_BITS-1;
  
  //convert to a c++ bitset object for efficiently packed representation.
  for (char c : input) {
    int nextNibble = hexConv[c-'0'];
    messageBits[b--] = nextNibble/1000;
    messageBits[b--] = (nextNibble-1000*(nextNibble/1000))/100;
    messageBits[b--] = (nextNibble-100*(nextNibble/100))/10;
    messageBits[b--] = (nextNibble-10*(nextNibble/10));
  }
  
  //after this block b will now contain the index of the first zero after the last 1 in the message, so that we stop processing at the correct point and ignore any trailing zeroes. 
  while (messageBits[b] == 0) {
    ++b;
  }
  --b;

  //process and output
  cout << processPacket(messageBits,b) << endl;
  
  return 0;
}
