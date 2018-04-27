
QT_GIT_URL    := https://code.qt.io/qt/qt5.git
QT_GIT_TAG    := 5.7
QT_SENTINEL   := .qtsrc.sentinel
QT_MKSPEC     := linux-mips-uclibc-g++
CONF_SENTINEL := .qtconf.sentinel

default: build

.PHONY: toolchain
toolchain:
	$(MAKE) -C ../../build/.support/toolchain

$(QT_SENTINEL):
	git clone $(QT_GIT_URL) src
	cd src && git checkout $(QT_GIT_TAG)
	cd src && ./init-repository --module-subset=qtbase
	cp -a $(QT_MKSPEC) src/qtbase/mkspecs/
	touch $(QT_SENTINEL)

.PHONY: configure
configure: $(CONF_SENTINEL)
$(CONF_SENTINEL): $(QT_SENTINEL) toolchain
	cd src && ./configure \
		-prefix /system/sdcard \
	        -extprefix $(PWD)/build/target \
		-hostprefix $(PWD)/build/host \
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
	touch $(CONF_SENTINEL)

.PHONY: build
build: $(CONF_SENTINEL)
	$(MAKE) -C src install

.PHONY: clean
clean:
	rm -rf $(QT_SENTINEL) $(CONF_SENTINEL) src
