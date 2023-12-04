#include "../../inc/base/shift_rows.h"

aes::ShiftRows::ShiftRows(unsigned char (*const s)[4],
                          const unsigned char INV) {
  unsigned char tmp[4][4];
  __builtin_memcpy(tmp, s, 16);
  signed char sht[4]{0, 1, 2, 3};

  neg(sht, INV);
  shiftConv(s, tmp, sht);
}

aes::ShiftRows::ShiftRows(unsigned char (*const s)[4], const unsigned char INV,
                          const unsigned char (*const W)[4]) {
  unsigned char tmp[4][4];
  __builtin_memcpy(tmp, s, 16);
  signed char sht[4];
  init(sht, s, W);
  neg(sht, INV);
  shiftMod(s, tmp, sht);
}

inline void aes::ShiftRows::neg(signed char *const sht,
                                const unsigned char INV) {
  if (INV)
    for (unsigned char i = 4; i--;)
      sht[i] *= -1;
}

inline void aes::ShiftRows::shiftConv(unsigned char (*const s)[4],
                                      const unsigned char (*const tmp)[4],
                                      const signed char *const sht) {
  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      s[i][j] = tmp[(i + sht[j]) & 3][j];
}

inline void aes::ShiftRows::shiftMod(unsigned char (*const s)[4],
                                     const unsigned char (*const tmp)[4],
                                     const signed char *const sht) {
  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      s[j][i] = tmp[j][(i + sht[j]) & 3];
}

inline void aes::ShiftRows::init(signed char *const sht,
                                 const unsigned char (*const S)[4],
                                 const unsigned char (*const W)[4]) {
  unsigned char val[4]{}, sorted[4];

  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      sorted[i] = val[i] ^= S[i][j] ^ W[i][j];

  sort(sorted);

  for (unsigned char i = 4; i--;)
    for (unsigned char j = 4; j--;)
      if (val[i] == sorted[j])
        sht[i] = j;
}

inline void aes::ShiftRows::sort(unsigned char *const val) {
  unsigned char n[2][3];

  if (val[0] < val[1])
    n[0][0] = val[0], n[0][2] = val[1];
  else
    n[0][0] = val[1], n[0][2] = val[0];

  if (val[2] < val[3])
    n[1][0] = val[2], n[1][2] = val[3];
  else
    n[1][0] = val[3], n[1][2] = val[2];

  if (n[0][0] < n[1][0])
    val[0] = n[0][0], n[0][1] = n[1][0];
  else
    val[0] = n[1][0], n[0][1] = n[0][0];

  if (n[0][2] > n[1][2])
    val[3] = n[0][2], n[1][1] = n[1][2];
  else
    val[3] = n[1][2], n[1][1] = n[0][2];

  if (n[0][1] < n[1][1])
    val[1] = n[0][1], val[2] = n[1][1];
  else
    val[2] = n[0][1], val[1] = n[1][1];
}
