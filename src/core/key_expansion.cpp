#include "../../inc/core/key_expansion.h"
#include "../../inc/base/sub_bytes.h"

aes::KeyExpansion::KeyExpansion(unsigned char (*const w)[4][4],
                                const unsigned char (*const KEY)[4]) {
  __builtin_memcpy(w, KEY, 16);

  for (unsigned char i = 0; i < 10; ++i)
    for (unsigned char tmp[4], j = 0;
         __builtin_memcpy(tmp, w[i][j + 3], 4), j < 4; ++j) {
      if (!j) {
        rotWord(tmp);
        SubBytes::subWord(tmp, 0);
        tmp[0] ^= this->RCON[i];
      }

      for (unsigned char k = 4; k--;)
        w[i + 1][j][k] = w[i][j][k] ^ tmp[k];
    }
}

inline void aes::KeyExpansion::rotWord(unsigned char *const w) {
  unsigned char tmp = w[0];

  for (unsigned char i = 0; i < 3; ++i)
    w[i] = w[i + 1];

  w[3] = tmp;
}

const unsigned char aes::KeyExpansion::RCON[10]{0x01, 0x02, 0x04, 0x08, 0x10,
                                                0x20, 0x40, 0x80, 0x1B, 0x36};
