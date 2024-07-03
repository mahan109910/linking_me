QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    home.cpp \
    information.cpp \
    job.cpp \
    main.cpp \
    managers.cpp \
    message.cpp \
    network.cpp \
    ok.cpp \
    signin.cpp \
    welcome.cpp \
    login.cpp

HEADERS += \
    home.h \
    information.h \
    job.h \
    managers.h \
    message.h \
    network.h \
    ok.h \
    signin.h \
    welcome.h \
    login.h

FORMS += \
    home.ui \
    information.ui \
    job.ui \
    managers.ui \
    message.ui \
    network.ui \
    ok.ui \
    signin.ui \
    welcome.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
