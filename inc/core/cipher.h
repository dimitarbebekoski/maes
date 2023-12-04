#ifndef CIPHER_H
#define CIPHER_H

namespace aes {
class Cipher {
public:
  Cipher(unsigned char (*const s)[4], const unsigned char (*const)[4][4],
         const unsigned char, const unsigned char);
};
} // namespace aes

#endif
