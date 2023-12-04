#include "../../inc/base/add_round_key.h"

aes::AddRoundKey::AddRoundKey(unsigned char (*const s)[4],
                              const unsigned char (*const W)[4]) {
  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      s[i][j] ^= W[i][j];
}
