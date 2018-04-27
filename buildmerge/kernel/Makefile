
PATH_SELF		:= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
KERNEL_CONFIG		:= src/.config
TIMESTAMP		:= $(shell date +"%Y%m%d%H%M%S")
KERNEL_HEADERS_FOLDER   := kernel-headers-$(TIMESTAMP)
KERNEL_HEADERS_TARBALL  := $(KERNEL_HEADERS_FOLDER).tgz

$(KERNEL_HEADERS_TARBALL): $(KERNEL_CONFIG)
	cd src && $(MAKE) headers_install INSTALL_HDR_PATH=$(PATH_SELF)$(KERNEL_HEADERS_FOLDER)
	tar czf $(KERNEL_HEADERS_TARBALL) $(KERNEL_HEADERS_FOLDER)

$(KERNEL_CONFIG):
	cp -a config $(KERNEL_CONFIG)

mrproper:
	cd src && $(MAKE) mrproper

clean:
	rm -rf kernel-headers-* kernel-headers-*.tgz

