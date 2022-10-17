QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 static static-runtime

INC_DIR = $${PWD}/include
SRC_DIR = $${PWD}/src
UI_DIR  = $${PWD}/ui

SOURCES += \
    $${SRC_DIR}/main.cpp \
    $${SRC_DIR}/frontend/mainwindow.cpp \
    $${SRC_DIR}/backend/game_field.cpp \
    $${SRC_DIR}/backend/cell.cpp \
    $${SRC_DIR}/backend/game.cpp \
    $${SRC_DIR}/frontend/cell_sprite.cpp

HEADERS += \
    $${INC_DIR}/frontend/mainwindow.h \
    $${INC_DIR}/backend/game.h \
    $${INC_DIR}/backend/game_field.h \
    $${INC_DIR}/backend/cell.h \
    $${INC_DIR}/frontend/cell_sprite.h


FORMS += \
    $${UI_DIR}/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
