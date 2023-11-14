MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD

HEADERS       = glwidget.h \
                carte.h \
                mesh.h \
                window.h \
                mainwindow.h \
                logo.h
SOURCES       = glwidget.cpp \
                carte.cpp \
                main.cpp \
                mesh.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp

RESOURCES += \
    shaders.qrc

QT           += widgets


