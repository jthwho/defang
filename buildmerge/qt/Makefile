
QT_GIT_URL     		:= https://code.qt.io/qt/qt5.git
QT_GIT_TAG     		:= 5.7
QT_SENTINEL    		:= .qtsrc.sentinel
QT_MKSPEC      		:= linux-mips-uclibc-g++
CONF_SENTINEL  		:= .qtconf.sentinel
BUILD_SENTINEL 		:= .qtbuild.sentinel
TOOLCHAIN_SENTINEL	:= .toolchain.sentinel

ifeq (,$(wildcard $(CONF_SENTINEL)))
TIMESTAMP      		:= $(shell date +"%Y%m%d%H%M%S")
CONF_NAME      		:= qt-$(QT_GIT_TAG)-$(TIMESTAMP)
else
CONF_NAME := $(shell cat $(CONF_SENTINEL))
endif

TARBALL_FILE   		:= $(CONF_NAME).tgz

default: $(TARBALL_FILE)

.PHONY: toolchain
toolchain: $(TOOLCHAIN_SENTINEL)

$(TOOLCHAIN_SENTINEL):
	$(MAKE) -C ../../build/.support/toolchain
	touch $(TOOLCHAIN_SENTINEL)

$(QT_SENTINEL):
	git clone $(QT_GIT_URL) src
	cd src && git checkout $(QT_GIT_TAG)
	cd src && ./init-repository --module-subset=qtbase
	cp -a $(QT_MKSPEC) src/qtbase/mkspecs/
	touch $(QT_SENTINEL)

.PHONY: configure
configure: $(CONF_SENTINEL)

$(CONF_SENTINEL): $(QT_SENTINEL) $(TOOLCHAIN_SENTINEL)
	cd src && ./configure \
		-prefix /system/sdcard \
	        -extprefix $(PWD)/$(CONF_NAME)/target \
		-hostprefix $(PWD)/$(CONF_NAME)/host \
		-no-gui \
		-no-widgets \
		-opensource \
		-confirm-license \
		-release \
		-strip \
		-xplatform $(QT_MKSPEC) \
		-no-compile-examples \
		-no-qml-debug \
		-nomake tests \
		-nomake examples
	echo $(CONF_NAME) > $(CONF_SENTINEL)

.PHONY: build
build: $(BUILD_SENTINEL)

$(BUILD_SENTINEL): $(CONF_SENTINEL)
	$(MAKE) -C src -j24
	+$(MAKE) -C src install
	touch $(BUILD_SENTINEL)

.PHONY: tarball
tarball: $(TARBALL_FILE)

$(TARBALL_FILE): $(BUILD_SENTINEL)
	tar czf $(TARBALL_FILE) $(CONF_NAME)


.PHONY: clean
clean:
	rm -rf $(QT_SENTINEL) $(CONF_SENTINEL) $(BUILD_SENTINEL) $(TARBALL_FILE) $(CONF_NAME) src
