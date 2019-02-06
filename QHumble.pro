TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
    humblebundleapi.cpp \
    settings.cpp \
    humbledb.cpp \
    db/purchase.cpp \
    db/product.cpp \
    db/download.cpp \
    db/file.cpp

RESOURCES += qml.qrc

!android {
    RESOURCES += notOnMobile.qrc
} else {
    RESOURCES += dummyMobile.qrc
}

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
    db/file.h

DISTFILES += \
    LICENSE.txt
