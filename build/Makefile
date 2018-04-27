
BUILD_PATH_BIN       := build/bin
BUILD_PATH_LIB       := build/lib
BUILD_SENTINEL       := .build.sentinel
SUPPORT_SENTINEL     := .support.sentinel

CLEAN_PATHS	     := build .*.sentinel

FOLDERS              := helloworld \
			defang

.DEFAULT_GOAL := folders

$(foreach i,$(FOLDERS),$(call TEMPLATE_QMAKE_MAKEFILE,$(i)))

$(SUPPORT_SENTINEL):
	$(MAKE) -C .support/toolchain
	$(MAKE) -C .support/qt
	$(MAKE) -C .support/kernel-headers
	touch $(SUPPORT_SENTINEL)

$(BUILD_SENTINEL): $(SUPPORT_SENTINEL)
	mkdir -p $(BUILD_PATH_BIN) $(BUILD_PATH_LIB)
	cp -a .support/qt/current/target/lib/libQt5Core.* $(BUILD_PATH_LIB)
	cp -a .support/qt/current/target/lib/libQt5Network.* $(BUILD_PATH_LIB)
	touch $(BUILD_SENTINEL)


.PHONY: folders
folders: $(BUILD_SENTINEL) 
	for folder in $(FOLDERS); do ( cd $$folder && ../bootstrap && $(MAKE); ); done

.PHONY: clean
clean:
	rm -rf $(CLEAN_PATHS)
	for folder in $(FOLDERS); do ( cd $$folder && if [ -f Makefile ]; then $(MAKE) clean; fi; ); done


distclean:
	rm -rf $(CLEAN_PATHS)
	for folder in $(FOLDERS); do ( cd $$folder && if [ -f Makefile ]; then $(MAKE) distclean; fi; ); done
	$(MAKE) -C .support/qt distclean
	$(MAKE) -C .support/toolchain distclean
	$(MAKE) -C .support/kernel-headers distclean

