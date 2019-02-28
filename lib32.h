#ifndef _LIB32_h
#define _LIB32_h 1

#include <cstddef>
#include <cstdint>


namespace lib32 {

  extern size_t strlen(const char* s);

  // Screen handling.
  struct cga_char {
    char ch;
    union {
      uint8_t color;
      struct {
        uint8_t fg:4;
        uint8_t bg:3;
        uint8_t blink:1;
      };
    };
  };

  extern cga_char* vidptr;


  extern void clrscr();
  extern void printat(unsigned x, unsigned y, const char* str);
  extern void printat(unsigned x, unsigned y, uint8_t attr, const char* str);
  extern void printat(unsigned x, unsigned y, unsigned long n);
  extern void printat(unsigned x, unsigned y, uint8_t attr, unsigned long n);

  extern void fail(const char* s);

} // namespace lib32

#endif // lib32.h
