#include "../../inc/test/main.h"
#include "../../inc/base/add_round_key.h"
#include "../../inc/core/cipher.h"
#include "../../inc/core/key_expansion.h"
#include "../../inc/test/file.h"
#include "../../inc/test/test.h"
#include "../../inc/test/timer.h"

int main(void) { return aes::Main::main(); }
const unsigned short aes::Main::MB05 = 512 * 1024 >> 4;
unsigned char aes::Main::key[4][4]{{'d', 'K', 'r', 'o'},
                                   {'9', 'W', 'a', 'h'},
                                   {'m', 'e', '#', 'd'},
                                   {'H', 'r', 'n', '7'}};
int aes::Main::main(void) { return table34() | table56() | table7(); }
int aes::Main::table7(void) {
  const long SIZES[5] = {16 >> 4, 32 >> 4, 64 >> 4, 128 >> 4, MB05};
  unsigned char in[MB05][4][4], s[MB05][4][4];
  File(in, sizeof in);
  unsigned char STR[4][4]{};
  for (unsigned char i = 5; i--;)
    for (unsigned char mod = 2; mod--;) {
      for (unsigned char w[11][4][4], inv = 2; STR[0][0] = SIZES[i], inv--;) {
        Timer timer(0, STR, key, mod, inv);
        __builtin_memcpy(s, in, sizeof in);
        KeyExpansion(w, key);
        for (unsigned short size = SIZES[i]; size--;)
          Cipher(s[size], w, mod, inv);
      }
    }

  return 0;
}
int aes::Main::table56(void) {
  unsigned char in[MB05][4][4], s[2][MB05][4][4], w[11][4][4];
  File(in, sizeof in);
  const float AVL[2][2] = {{49.9917641, 50.0056}, {49.9626999, 49.963707}};
  const unsigned char STR[2][4][4] = {{{'.', '/', '0', '_'},
                                       {'5', 'm', 'b', '.'},
                                       {'t', 'x', 't', ' '},
                                       {'f', 'i', 'l', 'e'}},
                                      {{}}};
  unsigned char(*const flipBufs[2])[4][4] = {&key, s[0]};
  const unsigned long flipBits[2] = {112, 3751};

  for (unsigned char tbl = 2; tbl--;)
    for (unsigned char mod = 2; mod--;) {
      __builtin_memcpy(s[0], in, sizeof in);
      __builtin_memcpy(s[1], in, sizeof in);

      for (unsigned char i = 2; i--;
           Test::flipBit(flipBufs[tbl], flipBits[tbl])) {
        Timer timer(STR[0], STR[1], key, mod, 0);
        KeyExpansion(w, key);
        for (unsigned short j = 0; j < MB05; ++j) {
          if (j)
            AddRoundKey(s[i][j], s[i][j - 1]);
          Cipher(s[i][j], w, mod, 0);
        }
      }

      float avl = 0;

      for (unsigned long i = 0; i < MB05; ++i)
        avl += Test::avalancheEffect(s[0][i], s[1][i]) / MB05;

      if (avl != AVL[tbl][mod])
        return 1;
    }

  return 0;
}
int aes::Main::table34() {
  unsigned char in[4][4];
  File(&in, 16);

  const unsigned char S[2][2][2][4][4]{{{{{0x5e, 0x7a, 0xd2, 0xbb},
                                          {0xff, 0x9b, 0xa1, 0x86},
                                          {0x19, 0xbd, 0xb1, 0x48},
                                          {0x40, 0xa9, 0x26, 0x8e}},
                                         {{0x55, 0xe3, 0x02, 0xbf},
                                          {0x16, 0xf6, 0x2a, 0xa7},
                                          {0xdd, 0xe7, 0x3a, 0xdf},
                                          {0x29, 0x78, 0x36, 0xa7}}},
                                        {{{0x5d, 0xcc, 0x92, 0x69},
                                          {0x1e, 0xc2, 0x74, 0xb4},
                                          {0xe7, 0xeb, 0x7e, 0x03},
                                          {0xd1, 0xde, 0x02, 0xd3}},
                                         {{0xd6, 0xba, 0x33, 0x8a},
                                          {0xc3, 0x61, 0x3a, 0x74},
                                          {0xb5, 0xfb, 0xeb, 0xa4},
                                          {0xea, 0x97, 0xb1, 0x10}}}},
                                       {{{{0xed, 0x9e, 0xbb, 0xe5},
                                          {0x1b, 0xbb, 0xc0, 0xaf},
                                          {0xbb, 0x3d, 0xe2, 0x07},
                                          {0xc4, 0xd1, 0xd0, 0x50}},
                                         {{0x55, 0xe3, 0x02, 0xbf},
                                          {0x16, 0xf6, 0x2a, 0xa7},
                                          {0xdd, 0xe7, 0x3a, 0xdf},
                                          {0x29, 0x78, 0x36, 0xa7}}},
                                        {{{0x5d, 0x2d, 0xa4, 0x39},
                                          {0x11, 0x04, 0x95, 0xc8},
                                          {0x2e, 0x17, 0xd3, 0x7f},
                                          {0x5c, 0x43, 0x22, 0x86}},
                                         {{0xd6, 0xba, 0x33, 0x8a},
                                          {0xc3, 0x61, 0x3a, 0x74},
                                          {0xb5, 0xfb, 0xeb, 0xa4},
                                          {0xea, 0x97, 0xb1, 0x10}}}}};
  const float AVL[2][2]{{42.96875, 49.21875}, {55.46875, 57.8125}};
  const struct Flip {
    unsigned char (*const buf)[4][4];
    const unsigned long BIT;
  } FLIPS[2]{{&in, 88}, {&key, 112}};

  for (unsigned char tbl = 2; tbl--;)
    if (check(S[tbl], AVL[tbl], in, FLIPS[tbl].buf, FLIPS[tbl].BIT))
      return 1;

  return 0;
}

int aes::Main::check(const unsigned char (*const S)[2][4][4],
                     const float *const AVL, unsigned char (*const in)[4],
                     unsigned char (*const buf)[4][4],
                     const unsigned char BIT) {
  for (unsigned char mod = 2; mod--;)
    for (unsigned char i = 2; i--; Test::flipBit(buf, BIT)) {
      for (unsigned char w[11][4][4], s[4][4], inv = 2; inv--;) {
        const unsigned char(*const P[3])[4] = {in, s, S[mod][i]};
        Timer timer(P[inv << 1], P[!inv], key, mod, inv);
        __builtin_memcpy(s, P[inv << 1], 16);
        KeyExpansion(w, key);
        Cipher(s, w, mod, inv);

        if (__builtin_memcmp(s, P[!inv << 1], 16))
          return 1;
      }

      for (unsigned char i = 2; i--;)
        if (Test::avalancheEffect(S[i][0], S[i][1]) != AVL[i])
          return 1;
    }
  return 0;
}
