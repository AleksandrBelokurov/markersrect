QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dashrectitem.cpp \
    graphicsview.cpp \
    main.cpp \
    mainwindow.cpp \
    marker.cpp \
    rectitem.cpp \
    rectmarkers.cpp

HEADERS += \
    dashrectitem.h \
    graphicsview.h \
    mainwindow.h \
    marker.h \
    rectitem.h \
    rectmarkers.h

TRANSLATIONS += \
    markersquare_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
