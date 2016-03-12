#include <algorithm>
#include <cstdint>
#include <cstring>
#include "lib32.h"
#include "multiboot.h"


multiboot::header header __attribute__((section(".startup")));

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
} * vidptr = (cga_char*) 0xb8000;	//video mem begins here.


void fail(const char* s);


extern "C"
void kmain(int magic, multiboot::info& info)
{
  if (! multiboot::multibooted(magic)) {
    fail("not multiboot");
    return;
  }

  static const char* str = "my first kernel @ " __DATE__ " " __TIME__;

  unsigned int i = 0;
  unsigned int j = 0;

  /* this loops clears the screen
   * there are 25 lines each of 80 columns; each element takes 2 bytes */
  while(j < 80 * 25) {
    /* blank character */
    vidptr[j] = (cga_char
		 ) { ' ', 0x07 };
    /* attribute-byte - light grey on black screen */
    //vidptr[j+1] = 0x07;
    j = j + 1;
  }

  j = 0;

  /* this loop writes the string to video memory */
  while(str[j] != '\0') {
    /* the character's ascii */
    vidptr[i].ch = str[j];
    /* attribute-byte: give character black bg and light grey fg */
    //vidptr[i+1] = 0x07;
    ++j;
    i = i + 1;
  }

  i = 80;
  str = "flags = ";
  for (j = 0; str[j]; ++j, ++i)
    vidptr[i].ch = str[j];
  auto v = info.flags;
  while (v >= 16) {
    ++i;
    v /= 16;
  }
  v = info.flags;
  do {
    vidptr[i--].ch = ((v % 0xf > 9) ? 'a' - 10 : '0') + v % 0xf;
    v >>= 4;
  } while (v != 0);

  return;
}


void fail(const char* s)
{
  std::transform(s, s + lib32::strlen(s), vidptr,
		 [](auto ch) { return (cga_char) { ch, 0x40 }; });
}
