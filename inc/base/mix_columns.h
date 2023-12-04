#ifndef MIX_COLUMNS_H
#define MIX_COLUMNS_H

namespace aes {
class MixColumns {
public:
  MixColumns(unsigned char (*const)[4], const unsigned char);

private:
  static const unsigned char MUL[2][4][256];
};
} // namespace aes

#endif
