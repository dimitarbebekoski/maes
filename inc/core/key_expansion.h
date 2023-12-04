#ifndef KEY_EXPANSION_H
#define KEY_EXPANSION_H

namespace aes {
class KeyExpansion {
public:
  KeyExpansion(unsigned char (*const)[4][4], const unsigned char (*const)[4]);

private:
  static inline void rotWord(unsigned char *const w);

  static const unsigned char RCON[10];
};
} // namespace aes

#endif
