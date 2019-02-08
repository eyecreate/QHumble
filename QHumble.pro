TEMPLATE = app

QT += qml quick quickcontrols2 widgets sql webview

SOURCES += main.cpp \
    humblebundleapi.cpp \
    settings.cpp \
    humbledb.cpp \
    db/purchase.cpp \
    db/product.cpp \
    db/download.cpp \
    db/file.cpp \
    db/customquerymodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    humblebundleapi.h \
    settings.h \
    humbledb.h \
    db/purchase.h \
    db/product.h \
    db/download.h \
    db/file.h \
    db/customquerymodel.h

DISTFILES += \
    LICENSE.txt

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android-ssl/aarch64/libcrypto.so \
        $$PWD/android-ssl/aarch64/libssl.so
}
