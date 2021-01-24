QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/api/algo/fnconvert.cpp \
    src/api/algo/fndatetime.cpp \
    src/api/audio/audiorecorderdialog.cpp \
    src/api/capture/capturewindow.cpp \
    src/api/color/colorobject.cpp \
    src/api/color/colortable.cpp \
    src/api/controls/card/selectcard.cpp \
    src/api/dialogs/selectvaluedialog.cpp \
    src/api/dialogs/setvaluedialog.cpp \
    src/api/draw/drawobject.cpp \
    src/api/sql/sqldef.cpp \
    src/api/sql/sqlitedao.cpp \
    src/api/sql/sqlitewrapper.cpp \
    src/datainfopage.cpp \
    src/datainfowidget.cpp \
    src/datainfowidgetitem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/showarticlewindow.cpp

HEADERS += \
    src/api/algo/fnconvert.h \
    src/api/algo/fndatetime.h \
    src/api/audio/audiorecorderdialog.h \
    src/api/capture/capturewindow.h \
    src/api/color/colorobject.h \
    src/api/color/colortable.h \
    src/api/controls/card/selectcard.h \
    src/api/dialogs/selectvaluedialog.h \
    src/api/dialogs/setvaluedialog.h \
    src/api/draw/drawobject.h \
    src/api/sql/sqldef.h \
    src/api/sql/sqlitedao.h \
    src/api/sql/sqlitewrapper.h \
    src/datainfopage.h \
    src/datainfowidget.h \
    src/datainfowidgetitem.h \
    src/mainwindow.h \
    src/showarticlewindow.h

FORMS += \
    src/api/audio/audiorecorderdialog.ui \
    src/api/capture/capturewindow.ui \
    src/api/controls/card/selectcard.ui \
    src/api/dialogs/selectvaluedialog.ui \
    src/api/dialogs/setvaluedialog.ui \
    src/datainfopage.ui \
    src/datainfowidget.ui \
    src/mainwindow.ui \
    src/showarticlewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DESTDIR=$$PWD/bin/
RC_ICONS=app.ico

RESOURCES += \
    app.qrc
