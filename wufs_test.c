
#include <stdio.h>
#include <stdlib.h>
#include "wufs_fs.h"
#include <linux/types.h>
#include "wufs.h"

char *i2bs(int i, __u8 *s) {
  s[32] = '\0';
  int index;
  for (index = 31; index >= 0; index--) {
    s[index] = (i & 1) + '0';
    i >>= 1;
  }
  return s;
}

void printBitfield(__u8 *f, int size) {
  while(size) {
    __u8 temp = *f;
    int index;
    for (index = 7; index >= 0; index--) {
      if(temp&1) putc('1', stdout);
      else putc('0', stdout);
      temp >>= 1;
    }
    f++;
    size--;
  }
  putc('\n', stdout);
}

int main() {
  __u8 binary[4] = {0};

  
  setBit(binary, 0);
  setBit(binary, 0);
  setBit(binary, 2);
  setBit(binary, 30);
  printBitfield(binary,4);

  clearBit(binary, 0);
  printBitfield(binary,4);

  printf("%d\n", getBit(binary, 30)); 
  printf("%d\n", getBit(binary, 31)); 

  printf("%d\n", findNextSet(binary, 0, 31));
  printf("%d\n", findNextSet(binary, 20, 32));

  printf("%d\n", findNextClear(binary, 20, 32));
  printf("%d\n", findNextClear(binary, 2, 32));

  printBitfield(binary,4);

  //printf("%s\n", i2bs((int)binary, out));
  return 0;
}


