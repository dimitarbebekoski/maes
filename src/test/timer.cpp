#include "../../inc/test/timer.h"
#include <cstdio>
#include <ctime>

aes::Timer::Timer(const unsigned char (*const IN)[4],
                  const unsigned char (*const S)[4],
                  const unsigned char (*const KEY)[4], const unsigned char MOD,
                  const unsigned char INV)
    : sec(), CIPHER(CIPHERS[MOD][INV]), end(-1) {
  P[0] = IN, P[1] = S, P[2] = KEY;
  gettime();
}

aes::Timer::~Timer() {
  gettime();
  state();
  std::printf(FMT, CIPHER, sec[0], sec[1], *P[2], *P[0], hex);
}

inline void aes::Timer::gettime() {
  std::timespec time;
  std::timespec_get(&time, 1);
  sec[0] += end * time.tv_sec;
  sec[1] += end * time.tv_nsec;
  end *= -1;
}

inline void aes::Timer::state() {
  for (unsigned char i = 0; i < 4; ++i)
    for (unsigned char j = 0; j < 4; ++j)
      std::sprintf(hex + 3 * ((i << 2) + j), "%02x ", P[1][i][j]);
}

const char aes::Timer::FMT[40] = "%sCipher %lu.%.9lus %.16s %.16s->%.47s\n";
const char aes::Timer::CIPHERS[2][2][7]{{"cnvFwd", "cnvInv"},
                                        {"modFwd", "modInv"}};
