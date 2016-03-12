#include "lib32.h"

namespace lib32 {

  size_t strlen(const char* s) {
    size_t i = 0;
    while (s[i] != '\0')
      ++i;
    return i;
  }

} // namespace lib32
