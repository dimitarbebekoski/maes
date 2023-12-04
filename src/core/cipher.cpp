#include "../../inc/core/cipher.h"
#include "../../inc/base/add_round_key.h"
#include "../../inc/base/mix_columns.h"
#include "../../inc/base/shift_rows.h"
#include "../../inc/base/sub_bytes.h"

aes::Cipher::Cipher(unsigned char (*const s)[4],
                    const unsigned char (*const W)[4][4],
                    const unsigned char MOD, const unsigned char INV) {
  if (!INV)
    for (unsigned char i = 0;; ++i) {
      AddRoundKey(s, W[i]);

      if (i == 10)
        break;

      if (!MOD) {
        SubBytes(s, 0);
        ShiftRows(s, 0);
      } else {
        SubBytes(s, 0, W[i + 1]);
        ShiftRows(s, 0, W[i + 1]);
      }

      if (i < 9)
        MixColumns(s, 0);
    }
  else
    for (unsigned char i = 10;; --i) {
      AddRoundKey(s, W[i]);

      if (i == 0)
        break;

      if (i < 10)
        MixColumns(s, 1);

      if (!MOD) {
        ShiftRows(s, 1);
        SubBytes(s, 1);
      } else {
        ShiftRows(s, 1, W[i]);
        SubBytes(s, 1, W[i]);
      }
    }
}
