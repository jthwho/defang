
CURRENT_PACKAGE_TARBALL    := $(shell readlink current_package)
CURRENT_PACKAGE            := $(basename $(CURRENT_PACKAGE_TARBALL))
CURRENT_PACKAGE_SENTINEL   := .$(CURRENT_PACKAGE).sentinel

default: $(CURRENT_PACKAGE_SENTINEL)

$(CURRENT_PACKAGE_SENTINEL): $(CURRENT_PACKAGE_TARBALL)
	tar xf $(CURRENT_PACKAGE_TARBALL)
	cp -a mkspecs $(CURRENT_PACKAGE)/host/
	( \
		echo [Paths] && \
		echo Prefix=$(PWD)/$(CURRENT_PACKAGE)/host && \
		echo Headers=$(PWD)/$(CURRENT_PACKAGE)/target/include && \
		echo Libraries=$(PWD)/$(CURRENT_PACKAGE)/target/lib \
	) > $(CURRENT_PACKAGE)/host/bin/qt.conf
	echo "QT -= gui" >> $(CURRENT_PACKAGE)/host/mkspecs/features/spec_pre.prf
	ln -f -s $(CURRENT_PACKAGE) current
	touch $(CURRENT_PACKAGE_SENTINEL)

.PHONY: distclean
distclean:
	rm -rf $(CURRENT_PACKAGE_SENTINEL) current $(CURRENT_PACKAGE)

