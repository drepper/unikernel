#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H 1

#include <cstdint>

namespace multiboot {

  struct header {
    static constexpr uint32_t header_magic = 0x1BADB002;

    uint32_t magic = header_magic;
    enum flags_type : uint32_t {
      none = 0,
      align = 1,
      video_mode = 4
    } flags;
    uint32_t checksum;

    constexpr header(flags_type f = flags_type::none)
      : flags(f), checksum(-(magic + static_cast<uint32_t>(flags))) {
      }
  };

  struct header_video : public header {
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;

    constexpr header_video(uint32_t m, uint32_t w, uint32_t h, uint32_t d,
			   header::flags_type f = header::flags_type::none);
  };


  constexpr header::flags_type operator|(header::flags_type l, header::flags_type r) {
    return static_cast<header::flags_type>(static_cast<uint32_t>(l)
					      + static_cast<uint32_t>(r));
  };


  inline constexpr header_video::header_video(uint32_t m, uint32_t w, uint32_t h, uint32_t d,
					      header::flags_type f)
    : header(f | flags_type::video_mode), mode_type(m), width(w), height(h), depth(d)
  {
  }


  constexpr uint32_t bootloader_magic = 0x2BADB002;

  bool multibooted(uint32_t magic) {
    return magic == bootloader_magic;
  }


  struct info {
  };

} // namespace multiboot

#endif // multiboot.h
