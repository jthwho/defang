#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1995, 1998, 2001, 2002 by Ralf Baechle
# Copyright (C) 2004  Maciej W. Rozycki
#

#
# Some DECstations need all possible sections of an ECOFF executable
#
ifdef CONFIG_MACH_DECSTATION
  e2eflag := -a
endif

#
# Drop some uninteresting sections in the kernel.
# This is only relevant for ELF kernels but doesn't hurt a.out
#
drop-sections := .reginfo .mdebug .comment .note .pdr .options .MIPS.options
strip-flags   := $(addprefix --remove-section=,$(drop-sections))

hostprogs-y := elf2ecoff

targets := vmlinux.ecoff
quiet_cmd_ecoff = ECOFF	  $@
      cmd_ecoff = $(obj)/elf2ecoff $(VMLINUX) $@ $(e2eflag)
$(obj)/vmlinux.ecoff: $(obj)/elf2ecoff $(VMLINUX) FORCE
	$(call if_changed,ecoff)

targets += vmlinux.bin
quiet_cmd_bin = OBJCOPY $@
      cmd_bin = $(OBJCOPY) -O binary $(strip-flags) $(VMLINUX) $@
$(obj)/vmlinux.bin: $(VMLINUX) FORCE
	$(call if_changed,bin)

targets += vmlinux.srec
quiet_cmd_srec = OBJCOPY $@
      cmd_srec = $(OBJCOPY) -S -O srec $(strip-flags) $(VMLINUX) $@
$(obj)/vmlinux.srec: $(VMLINUX) FORCE
	$(call if_changed,srec)
ifeq ($(shell uname -m), x86_64)
UIMAGE_LOADADDR  = $(VMLINUX_LOAD_ADDRESS)
else
UIMAGE_LOADADDR  = $(subst ffffffff,,$(VMLINUX_LOAD_ADDRESS))
endif
UIMAGE_ENTRYADDR = $(VMLINUX_ENTRY_ADDRESS)

ifeq ($(CONFIG_KERNEL_LZMA),y)
  uImage_compress_type = lzma
else
  uImage_compress_type = gzip
endif

$(obj)/vmlinux.bin.$(uImage_compress_type): $(obj)/vmlinux.bin FORCE
	$(call if_changed,$(uImage_compress_type))

targets += uImage.$(uImage_compress_type)
$(obj)/uImage.$(uImage_compress_type): $(obj)/vmlinux.bin.$(uImage_compress_type) FORCE
	$(call if_changed,uimage,$(uImage_compress_type))

targets += uImage
$(obj)/uImage: $(obj)/uImage.$(uImage_compress_type) FORCE
	@ln -sf $(notdir $<) $@
	@echo '  Image $@ is ready'
