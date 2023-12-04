#include "../../inc/test/test.h"

float aes::Test::avalancheEffect(const unsigned char (*const S0)[4],
                                 const unsigned char (*const S1)[4]) {
  unsigned char pops = 0;

  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      pops += __builtin_popcount(S0[i][j] ^ S1[i][j]);

  return pops * .78125;
}

void aes::Test::flipBit(unsigned char (*const str)[4][4], const unsigned long K) {
  const unsigned char EL = (K >> 3) - 1;
  str[0][EL >> 2][EL & 3] ^= 1 << (K & 7);
}
