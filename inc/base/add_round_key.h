#ifndef ADD_ROUND_KEY_H
#define ADD_ROUND_KEY_H

namespace aes {
class AddRoundKey {
public:
  AddRoundKey(unsigned char (*const)[4], const unsigned char (*const)[4]);
};
} // namespace aes

#endif
