#ifndef SHIFT_ROWS_H
#define SHIFT_ROWS_H

namespace aes {
class ShiftRows {
public:
  ShiftRows(unsigned char (*const)[4], const unsigned char);
  ShiftRows(unsigned char (*const)[4], const unsigned char,
            const unsigned char (*const)[4]);

private:
  static inline void neg(signed char *const, const unsigned char);
  static inline void shiftConv(unsigned char (*const)[4],
                               const unsigned char (*const)[4],
                               const signed char *const);
  static inline void shiftMod(unsigned char (*const)[4],
                              const unsigned char (*const)[4],
                              const signed char *const);
  static inline void init(signed char *const, const unsigned char (*const)[4],
                          const unsigned char (*const)[4]);
  static inline void sort(unsigned char *const);
};
} // namespace aes

#endif
