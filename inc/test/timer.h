#ifndef TIMER_H
#define TIMER_H

namespace aes {
class Timer {
public:
  Timer(const unsigned char (*const)[4], const unsigned char (*const)[4],
        const unsigned char (*const)[4], const unsigned char,
        const unsigned char);
  ~Timer();

private:
  inline void state(), gettime();

  unsigned long sec[2];
  const unsigned char (*P[3])[4];
  const char *const CIPHER;
  signed char end;

  char hex[47];
  static const char CIPHERS[2][2][7], FMT[];
};
} // namespace aes

#endif
