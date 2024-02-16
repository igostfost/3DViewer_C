QT       += core gui openglwidgets
LIBS     += -framework GLUT -framework OpenGL -framework Cocoa

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../transformations.c \
    ../vert.c \
    lib/3rdparty/giflib/dgif_lib.c \
    lib/3rdparty/giflib/egif_lib.c \
    lib/3rdparty/giflib/gif_err.c \
    lib/3rdparty/giflib/gif_font.c \
    lib/3rdparty/giflib/gif_hash.c \
    lib/3rdparty/giflib/gifalloc.c \
    lib/3rdparty/giflib/quantize.c \
    lib/gifimage/qgifimage.cpp \
    main.cpp \
    mainwindow.cpp \
    winopengl.cpp

HEADERS += \
    ../viewer.h \
    lib/3rdparty/giflib/gif_lib.h \
    lib/gifimage/qgifimage.h \
    mainwindow.h \
    winopengl.h

FORMS += \
    mainwindow.ui
    macx:ICON = $${PWD}/log.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cube.obj
