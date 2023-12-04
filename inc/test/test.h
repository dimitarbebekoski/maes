#ifndef TEST_H
#define TEST_H

namespace aes {
class Test {
public:
  static float avalancheEffect(const unsigned char (*const)[4],
                               const unsigned char (*const)[4]);
  static void flipBit(unsigned char (*const)[4][4], const unsigned long);
};
} // namespace aes

#endif
