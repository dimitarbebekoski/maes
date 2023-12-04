#ifndef MAIN_H
#define MAIN_H

namespace aes {
class Main {
public:
  static int main(void);

private:
  static unsigned char key[4][4];
  static const unsigned short MB05;

  static int table34(void), table56(void), table7(void);
  static int check(const unsigned char (*const S)[2][4][4],
                   const float *const AVL, unsigned char (*const in)[4],
                   unsigned char (*const buf)[4][4], const unsigned char BIT);
};
} // namespace aes

#endif
