#include "../../inc/test/file.h"
#include <fcntl.h>
#include <unistd.h>

aes::File::File(unsigned char (*const buf)[4][4], const long SIZE) {
  int fd = open("0_5mb.txt", 0);
  read(fd, buf, SIZE);
  close(fd);
}
