Updated makefile
# Change the CURRENT_TOOLCHAIN variable with the name of the current toolchain
# if it changes.  The name should reference a tarball of the same name which,
# when extraced, will create a folder with the same name that contains the
# toolchain.
CURRENT_TOOLCHAIN := toolchain-mips-gcc472-glibc216-64bit-20180427020849
CURRENT_TOOLCHAIN_TARBALL := $(CURRENT_TOOLCHAIN).tar.gz
CURRENT_TOOLCHAIN_SENTINEL := .$(CURRENT_TOOLCHAIN).sentinel

default: $(CURRENT_TOOLCHAIN_SENTINEL)

$(CURRENT_TOOLCHAIN_SENTINEL): $(CURRENT_TOOLCHAIN_TARBALL)
	tar xf $(CURRENT_TOOLCHAIN_TARBALL)
	ln -f -s $(CURRENT_TOOLCHAIN) current
	touch $(CURRENT_TOOLCHAIN_SENTINEL)

.PHONY: distclean
distclean:
	rm -rf $(CURRENT_TOOLCHAIN_SENTINEL) current $(CURRENT_TOOLCHAIN)

