#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H 1

#undef i386
#include <cstdint>
#include <tuple>

namespace multiboot1 {

  struct header {
    static constexpr uint32_t header_magic = 0x1BADB002;

    uint32_t magic = header_magic;
    enum flags_type : uint32_t {
      none = 0,
      align = 1,
      video_mode = 4,
      memory_map = 64
    } flags;
    uint32_t checksum;

    constexpr header(flags_type f = flags_type::none)
      : flags(f), checksum(-(magic + static_cast<uint32_t>(flags))) {}

    // std::pair<uintptr_t,uintptr_t> get_reserved() const {
    //   return std::make_pair(uintptr_t(this), 
    // }
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
    return static_cast<header::flags_type>(static_cast<uint32_t>(l) + static_cast<uint32_t>(r));
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


  // The section header table for ELF.
  struct elf_section_header_table {
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
  };


  struct info {
    // Multiboot info version number.
    uint32_t flags;

    // Available memory from BIOS.
    uint32_t mem_lower;
    uint32_t mem_upper;

    // "root" partition
    uint32_t boot_device;

    // Kernel command line
    uint32_t cmdline;

    // Boot-Module list
    uint32_t mods_count;
    uint32_t mods_addr;

    elf_section_header_table elf_sec;

    // Memory Mapping buffer
    uint32_t mmap_length;
    uint32_t mmap_addr;

    // Drive Info buffer
    uint32_t drives_length;
    uint32_t drives_addr;

    // ROM configuration table
    uint32_t config_table;

    // Boot Loader Name
    uint32_t boot_loader_name;

    // APM table
    uint32_t apm_table;

    // Video
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
  };

} // namespace multiboot1


namespace multiboot2 {

  struct header {
    static constexpr uint32_t header_magic = 0xe85250d6;

    uint32_t magic = header_magic;
    enum arch_type : uint32_t {
      i386 = 0,
      mips32 = 4
    } arch;
    uint32_t header_len;
    uint32_t checksum;

    constexpr header(arch_type a)
      : arch(a), header_len(0), checksum(-(magic + static_cast<uint32_t>(a)))
    {
    }
  };


  constexpr uint32_t bootloader_magic = 0x36d76289;

  bool multibooted(uint32_t magic) { return magic == bootloader_magic; }


  // The section header table for ELF.
  struct elf_section_header_table {
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
  };


  struct info {
    // Multiboot info version number.
    uint32_t flags;

    // Available memory from BIOS.
    uint32_t mem_lower;
    uint32_t mem_upper;

    // "root" partition
    uint32_t boot_device;

    // Kernel command line
    uint32_t cmdline;

    // Boot-Module list
    uint32_t mods_count;
    uint32_t mods_addr;

    elf_section_header_table elf_sec;

    // Memory Mapping buffer
    uint32_t mmap_length;
    uint32_t mmap_addr;

    // Drive Info buffer
    uint32_t drives_length;
    uint32_t drives_addr;

    // ROM configuration table
    uint32_t config_table;

    // Boot Loader Name
    uint32_t boot_loader_name;

    // APM table
    uint32_t apm_table;

    // Video
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
  };

} // namespace multiboot2

#endif // multiboot.h
