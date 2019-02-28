#include "lib32.h"

namespace lib32 {

  size_t strlen(const char* s) {
    size_t i = 0;
    while (s[i] != '\0')
      ++i;
    return i;
  }


  cga_char* vidptr = (cga_char*) 0xb8000;

  void clrscr()
  {
	  unsigned int j = 0;

	  /* this loops clears the screen.
	     There are 25 lines each of 80 columns; each element takes 2 bytes.  */
	  while (j < 80 * 25) {
	    /* blank character */
	    vidptr[j] = (cga_char) { ' ', 0x07 };
	    j = j + 1;
	  }
  }


  void printat(unsigned x, unsigned y, const char* str)
  {
    auto* v = &vidptr[y * 80 + x];
    while (*str)
      (v++)->ch = *str++;
  }


  void printat(unsigned x, unsigned y, uint8_t attr, const char* str)
  {
    auto* v = &vidptr[y * 80 + x];
    while (*str)
      *(v++) = { *str++, attr };
  }


  void printat(unsigned x, unsigned y, unsigned long n)
  {
    auto* v = &vidptr[y * 80 + x];
    char buf[2 * sizeof(n)];
    char* cp = buf + 2 * sizeof(n);
    if (n == 0)
      *--cp = '0';
    else
      while (n > 0) {
        *--cp = "0123456789abcdef"[n & 15];
        n >>= 4;
      }
    while (cp < buf + 2 * sizeof(n))
      (v++)->ch = *cp++;
  }


  void printat(unsigned x, unsigned y, uint8_t attr, unsigned long n)
  {
    auto* v = &vidptr[y * 80 + x];
    char buf[2 * sizeof(n)];
    char* cp = buf + 2 * sizeof(n);
    if (n == 0)
      *--cp = '0';
    else
      while (n > 0) {
        *--cp = "0123456789abcdef"[n & 15];
        n >>= 4;
      }
    while (cp < buf + 2 * sizeof(n))
      *(v++) = { *cp++, attr };
  }


  void fail(const char* s)
  {
    lib32::printat(0, 0, 0x40, "FAIL: ");
    lib32::printat(0, 6, 0x40, s);
  }

} // namespace lib32
