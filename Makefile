CC = gcc -ffreestanding
CXX = g++ -std=gnu++17 -ffreestanding
LD = ld
# QEMU = qemu-system-i386
QEMU = qemu-kvm

CXXFLAGS = $(DEBUG) $(OPT)
ASFLAGS = $(DEBUG) $(OPT)
DEBUG = -g
OPT = -O2

TARGET = kernel
CXXOBJS32 = kmain32.o
ASOBJS32 = boot32.o

OBJS = $(ASOBJS32) $(CXXOBJS32)
DEPS = $(ASOBJS32:.o=.d) $(CXXOBJS32:.o=.d)

kmain32.o: CXXFLAGS += -m32
boot32.o: ASFLAGS += -m32

include Rules.mk

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) kernel.map
	$(Q)$(LD) -m elf_i386 -T kernel.map -o $@ $^

.PHONY: run
run: all
	$(QEMU) -kernel kernel

.PHONY: clean distclean
clean:
	-rm -f $(TARGET) $(OBJS)
distclean: clean
	-rm -f $(DEPS)

-include $(DEPS)
