// using polynomial rolling algo
// hash = x1*A^0 + x2*A^i.....xn*A^n

#include "hashFn.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int hashFn(char *value, int tableSize) {
  long long p = 31, m = 1e9 + 7;
  long long hash = 0;
  long long p_pow = 1;
  for (int i = 0; i < strlen(value); i++) {
    hash = (hash + (value[i] - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash % tableSize;
}

/*int main (void) {*/
/*char* var = "pooopoo";*/
/*int value = hashFn(var, 10);*/
/*printf("hashing value: %s, got key %d\n",var,value);*/
/*return 0;*/
/*}*/
