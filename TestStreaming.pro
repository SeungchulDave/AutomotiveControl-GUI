QT       += core gui network multimedia multimediawidgets openglwidgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



INCLUDEPATH += $$PWD\install\include  \


LIBS +=    $$PWD\bin\libopencv_core454d.dll    \
           $$PWD\bin\libopencv_highgui454d.dll  \
           $$PWD\bin\libopencv_imgproc454d.dll   \
           $$PWD\bin\libopencv_imgcodecs454d.dll  \
           $$PWD\bin\libopencv_video454d.dll       \
           $$PWD\bin\libopencv_videoio454d.dll      \

SOURCES += \
    controlform.cpp \
    focusform.cpp \
    main.cpp       \
    mainwindow.cpp \
    messagewidget.cpp \
    settingform.cpp \
    videoform.cpp    \



HEADERS += \
    controlform.h \
    focusform.h \
    mainwindow.h \
    messagewidget.h \
    settingform.h \
    videoform.h


FORMS += \
    controlform.ui \
    focusform.ui \
    mainwindow.ui \
    messagewidget.ui \
    videoform.ui  \
    settingform.ui

# Default rules for deployment.

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


#DISTFILES +=

#win32:Debug:DESTDIR = $$PWD/../Bin/x64Debug
#win32:Release:DESTDIR = $$PWD/../Bin/x64Release
#android:DESTDIR = $$PWD/../Bin/android/arm64-v8a

RESOURCES += \
    icon.qrc

