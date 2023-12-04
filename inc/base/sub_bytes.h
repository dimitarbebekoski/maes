#ifndef SUB_BYTES_H
#define SUB_BYTES_H

namespace aes {
class SubBytes {
public:
  SubBytes(unsigned char (*const)[4], const unsigned char);
  SubBytes(unsigned char (*const)[4], const unsigned char,
           const unsigned char (*const)[4]);

  static void subWord(unsigned char *const, const unsigned char);

private:
  static inline void sub(unsigned char (*const)[4], const unsigned char);
  static inline void xorKey(unsigned char (*const)[4],
                            const unsigned char (*const)[4]);

  static const unsigned char SBOX[2][256];
};
} // namespace aes

#endif
