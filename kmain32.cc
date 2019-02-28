#include "lib32.h"
#include "multiboot.h"


multiboot1::header header __attribute__((section(".startup")));

extern "C"
void kmain(int magic, multiboot1::info& info)
{
  if (! multiboot1::multibooted(magic)) {
    lib32::fail("not multiboot");
    return;
  }

  lib32::clrscr();

  static const char* str = "my first kernel @ " __DATE__ " " __TIME__;


  unsigned int i = 0;
  unsigned int j = 0;

  lib32::printat(0, 0, str);

  lib32::printat(0, 1, "flags =");
  lib32::printat(8, 1, info.flags);
}
