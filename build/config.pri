#
#

OBJECTS_DIR=.build/obj
MOC_DIR=.build/moc
RCC_DIR=.build/rcc
UI_DIR=.build/ui

LIBS += -Wl,-rpath,\'\$$ORIGIN/../lib\' \
        -Wl,-rpath,/system/sdcard/lib

INCLUDEPATH += $$PWD/.support/kernel-headers/include

CONFIG += silent

