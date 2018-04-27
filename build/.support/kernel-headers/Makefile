
PATH_SELF                  := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
CURRENT_PACKAGE_TARBALL    := $(shell readlink current_package)
CURRENT_PACKAGE            := $(basename $(CURRENT_PACKAGE_TARBALL))
CURRENT_PACKAGE_SENTINEL   := .$(CURRENT_PACKAGE).sentinel

default: $(CURRENT_PACKAGE_SENTINEL)

$(CURRENT_PACKAGE_SENTINEL): $(CURRENT_PACKAGE_TARBALL)
	tar xf $(CURRENT_PACKAGE_TARBALL)
	ln -f -s $(CURRENT_PACKAGE) current
	touch $(CURRENT_PACKAGE_SENTINEL)

.PHONY: distclean
distclean:
	rm -rf $(CURRENT_PACKAGE_SENTINEL) current $(CURRENT_PACKAGE)

