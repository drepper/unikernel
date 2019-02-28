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

  lib32::printat(0, 2, "&buf =");
  static char buf[16];
  lib32::printat(7, 2, uintptr_t(buf));

  unsigned* p = (unsigned*) 0x8000000;
  lib32::printat(0, 3, "@");
  lib32::printat(1, 3, uintptr_t(p));
  lib32::printat(0, 4, "before: ");
  lib32::printat(8, 4, *p);
  *p = 0x12345;
  lib32::printat(0, 5, "after : ");
  lib32::printat(8, 5, *p);

  p = (unsigned*) 0x8000000-1;
  lib32::printat(0, 7, "@");
  lib32::printat(1, 7, uintptr_t(p));
  lib32::printat(0, 8, "before: ");
  lib32::printat(8, 8, *p);
  *p = 0x12345;
  lib32::printat(0, 9, "after : ");
  lib32::printat(8, 9, *p);

  p = (unsigned*) 0x40000000;
  lib32::printat(0, 11, "@");
  lib32::printat(1, 11, uintptr_t(p));
  lib32::printat(0, 12, "before: ");
  lib32::printat(8, 12, *p);
  *p = 0x12345;
  lib32::printat(0, 13, "after : ");
  lib32::printat(8, 13, *p);
}
