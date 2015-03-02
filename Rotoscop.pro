TEMPLATE += app

QT += multimedia multimediawidgets widgets gui declarative testlib

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    project.cpp \
    dialognewproject.cpp \
    drawinglabel.cpp \
    settingsdialog.cpp \
    preview.cpp \
    dialogthread.cpp \
    threadexportvideo.cpp \
    historique.cpp

HEADERS += \
    mainwindow.h \
    project.h \
    dialognewproject.h \
    drawinglabel.h \
    settingsdialog.h \
    preview.h \
    dialogthread.h \
    threadexportvideo.h \
    historique.h

FORMS += \
    mainwindow.ui \
    dialognewproject.ui \
    settingsdialog.ui \
    preview.ui \
    dialogthread.ui

RESOURCES += \
    ressources.qrc
